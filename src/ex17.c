#include <stdio.h>  // fopen fclose fread fwrite fflush rewind printf perror
#include <stdlib.h> // malloc free exit atoi
#include <errno.h>  // errno
#include <string.h> // strncpy

#define MAX_DATA 512
#define MAX_ROWS 100

struct Address {
  int id;
  int set;
  char *name;
  char *email;
};

struct Database {
  int max_rows;
  int max_data;
  struct Address *rows;
};

struct Connection {
  FILE *file;
  struct Database *db;
};

void Database_close(struct Connection *conn);

void die(const char *message, struct Connection *conn)
{
  if (errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }

  Database_close(conn);

  exit(1);
}

struct Address Address_create(int id, int max_data)
{
  struct Address addr = { .id = id, .set = 0 };

  addr.name = malloc(max_data * sizeof (char));
  addr.name[0] = '\0';

  addr.email = malloc(max_data * sizeof (char));
  addr.email[0] = '\0';

  return addr;
}

void Address_print(struct Address* addr)
{
  printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection* conn)
{
  rewind(conn->file);

  struct Database *db = conn->db;

  int rc = fread(&db->max_rows, sizeof (int), 1, conn->file);
  if (rc != 1) {
    die("Failed to read db->max_rows", conn);
  }

  rc = fread(&db->max_data, sizeof (int), 1, conn->file);
  if (rc != 1) {
    die("Failed to read db->max_data", conn);
  }

  db->rows = malloc(db->max_rows * sizeof (struct Address));

  for (int i = 0; i < db->max_rows; i++) {
    // TODO extract into function
    struct Address addr = Address_create(i, db->max_data);
    rc = fread(&addr.id, sizeof (int), 1, conn->file);
    if (rc != 1) {
      die("Failed to read addr.id", conn);
    }
    rc = fread(&addr.set, sizeof (int), 1, conn->file);
    if (rc != 1) {
      die("Failed to read addr.set", conn);
    }
    rc = fread(addr.name, sizeof (char), db->max_data, conn->file);
    if (rc != db->max_data) {
      die("Failed to read addr.name", conn);
    }
    rc = fread(addr.email, sizeof (char), db->max_data, conn->file);
    if (rc != db->max_data) {
      die("Failed to write addr.email", conn);
    }

    db->rows[i] = addr;
  }
}

struct Connection*
Database_open(const char *filename, char mode)
{
  struct Connection *conn = malloc(sizeof (struct Connection));
  if (!conn) {
    die("Memory error", NULL);
  }

  conn->db = malloc(sizeof (struct Database));
  if (!conn->db) {
    die("Memory error", conn);
  }

  if (mode == 'c') {
    conn->file = fopen(filename, "w");
  } else {
    conn->file = fopen(filename, "r+");

    if (conn->file) {
      Database_load(conn);
    }
  }

  if (!conn->file) {
    die("Failed to open the file", conn);
  }

  return conn;
}

void Database_close(struct Connection *conn)
{
  if (conn) {
    if (conn->file) {
      fclose(conn->file);
    }
    struct Database *db = conn->db;
    if (db) {
      for (int i = 0; i < db->max_rows; i++) {
        struct Address *addr = &db->rows[i];
        free(addr->name);
        free(addr->email);
      }
      free(db->rows);
      free(db);
    }
    free(conn);
  }
}

void Database_write(struct Connection *conn)
{
  rewind(conn->file);

  struct Database *db = conn->db;

  int rc = fwrite(&db->max_rows, sizeof (int), 1, conn->file);
  if (rc != 1) {
    die("Failed to write db->max_rows", conn);
  }

  rc = fwrite(&db->max_data, sizeof (int), 1, conn->file);
  if (rc != 1) {
    die("Failed to write db->max_data", conn);
  }

  for (int i = 0; i < db->max_rows; i++) {
    // TODO extract into function
    struct Address addr = conn->db->rows[i];
    rc = fwrite(&addr.id, sizeof (int), 1, conn->file);
    if (rc != 1) {
      die("Failed to write addr.id", conn);
    }
    rc = fwrite(&addr.set, sizeof (int), 1, conn->file);
    if (rc != 1) {
      die("Failed to write addr.set", conn);
    }
    rc = fwrite(addr.name, sizeof (char), db->max_data, conn->file);
    if (rc != db->max_data) {
      die("Failed to write addr.name", conn);
    }
    rc = fwrite(addr.email, sizeof (char), db->max_data, conn->file);
    if (rc != db->max_data) {
      die("Failed to write addr.email", conn);
    }
  }

  rc = fflush(conn->file);
  if (rc != 0) {
    die("Cannot flush database.", conn);
  }
}

void Database_create(struct Connection *conn, int max_rows, int max_data)
{
  struct Database *db = conn->db;
  db->max_rows = max_rows;
  db->max_data = max_data;

  db->rows = malloc(max_rows * sizeof (struct Address));

  for (int i = 0; i < max_rows; i++) {
    conn->db->rows[i] = Address_create(i, max_data);
  }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
  struct Database *db = conn->db;

  if (id > db->max_rows - 1) {
    die("ID is too large.", conn);
  }

  struct Address *addr = &db->rows[id];
  if (addr->set) {
    die("Already set, delete it first", conn);
  }

  addr->set = 1;

  strncpy(addr->name, name, db->max_data);
  addr->name[db->max_data - 1] = '\0';

  strncpy(addr->email, email, db->max_data);
  addr->email[db->max_data - 1] = '\0';
}

void Database_get(struct Connection *conn, int id)
{
  struct Address *addr = &conn->db->rows[id];

  if (addr->set) {
    Address_print(addr);
  } else {
    die("ID is not set", conn);
  }
}

void Database_delete(struct Connection *conn, int id)
{
  struct Database *db = conn->db;
  struct Address *addr = &db->rows[id];

  addr->set = 0;
  addr->name[0] = '\0';
  addr->email[0] = '\0';
}

void Database_list(struct Connection *conn) {
  struct Database *db = conn->db;

  for (int i = 0; i < db->max_rows; i++) {
    struct Address *addr = &db->rows[i];
    if (addr->set) {
      Address_print(addr);
    }
  }
}

int main(int argc, char *argv[])
{
  if (argc <= 2) {
    die("USAGE: ex17 <dbfile> <action> [action params]", NULL);
  }

  char *filename = argv[1];
  char action = argv[2][0];

  struct Connection *conn = Database_open(filename, action);
  int id = 0;

  if (argc >= 4) {
    id = atoi(argv[3]);
  }

  switch (action) {
    case 'c':
      if (argc != 5) {
        die("Need `max_rows` and `max_data` to create", conn);
      }

      int max_rows = atoi(argv[3]);
      int max_data = atoi(argv[4]);
      Database_create(conn, max_rows, max_data);
      Database_write(conn);
      break;

    case 'g':
      if (argc != 4) {
        die("Need an id to get", conn);
      }

      Database_get(conn, id);
      break;

    case 's':
      if (argc != 6) {
        die("Need id, name and email to set", conn);
      }

      Database_set(conn, id, argv[4], argv[5]);
      Database_write(conn);
      break;

    case 'd':
      if (argc != 4) {
        die("Need id to delete", conn);
      }

      Database_delete(conn, id);
      Database_write(conn);
      break;

    case 'l':
      Database_list(conn);
      break;

    default:
      die("Invalid action: c=create, g=get, s=set, d=delete, l=list", conn);
  }

  Database_close(conn);

  return 0;
}
