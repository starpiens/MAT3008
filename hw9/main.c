#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  float x;
  float y;
  float xp;
  float yp;
} Data;

typedef struct {
  Data *data;
  size_t size;
  size_t _capacity;
} Datalist;

Datalist *read_data(const char *filename) {
    FILE *ifp = fopen(filename, "r");
    if (ifp == NULL) {
        fprintf(stderr, "Failed to open file %s\n", filename);
        exit(1);
    }

    Datalist *datalist = malloc(sizeof(Datalist));
    datalist->data = malloc(sizeof(Data));
    datalist->size = 0;
    datalist->_capacity = 1;
    float x, y, xp, yp;
    while(fscanf(ifp, "%f %f %f %f", &x, &y, &xp, &yp) == 4) {
        datalist->data[datalist->size].x = x;
        datalist->data[datalist->size].y = y;
        datalist->data[datalist->size].xp = xp;
        datalist->data[datalist->size].yp = yp;
        if (++datalist->size == datalist->_capacity) {
            datalist->_capacity *= 2;
            datalist->data = realloc(datalist->data, sizeof(Data) * (datalist->_capacity));
        }
    }
    fclose(ifp);
    return datalist;
}

void free_datalist(Datalist *datalist) {
    free(datalist->data);
    free(datalist);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <data_file>\n", argv[0]);
        exit(1);
    }
    Datalist *datalist = read_data(argv[1]);

    // Do something
    for (int i = 0; i < datalist->size; i++) {
        printf("%f %f %f %f\n",
               datalist->data[i].x,
               datalist->data[i].y,
               datalist->data[i].xp,
               datalist->data[i].yp);
    }

    free_datalist(datalist);
    return 0;
}