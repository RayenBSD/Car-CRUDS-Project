#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// CRUDS
// C - Create
// R - Read
// U - Update
// D - delete
// S - Save

// Car - Brand, Model, Color, Year, Price
typedef struct {
  char brand[20], model[20], color[20];
  int year, price;
} Car;


// Delete
void deleteCar();

// Menu
void menu(int *);

// Cases
// case1 - create
void case1();
// case2 - read
void case2();
// case3 - update
void case3();
// case4 - delete
void case4();
// case5 - rename file
void case5();

// general functions
bool checkCarInfo(Car);
void handleFileData(short, char*, Car*);

/* Main */
int main() {


  // create the choice var to get the choice from the menu func
  int choice;

  // main loop for all programme
  bool mainLoop = true;

  // start the main programme
  while (mainLoop) {

    // call the menu func to get the choice
    menu(&choice);

    // switch the choice
    switch (choice) {
    case 0:
      exit(0);
      break;
    case 1:
      case1();
      break;
    case 2: 
      case2();
      break;
    case 3:
      case3();
      break;
    case 4:
      case4();
      break;
    case 5:
      case5();
      break;
    default:
      printf("\n\n\nWrong choice\n\n\n");
    }
  }

  return 0;
}

void menu(int *choice) {
  // print the menu

  do {
    /*
      start a loop to get the choice
      and
      to verify the input(choice)
    */
    printf("1.Add new car\n");
    printf("2.Get car info\n");
    printf("3.Update car info\n");
    printf("4.delete a car\n");
    printf("5.Rename a file\n");
    printf("0.exit\n> ");

    // get the input(choice)
    scanf("%d", choice);
    system("clear");
    /*
      if the choice is correct
      then
      exit the function else loop again
    */
  } while (!(*choice >= 0 && *choice <= 5));
}

// case 1
void case1() {

  Car car;
  
  do {
    printf("Enter the Brand: ");
    scanf(" %19s", car.brand);
  
    printf("Enteer the Model: ");
    scanf(" %19s", car.model);
  
    printf("Enteer the Color: ");
    scanf(" %19s", car.color);
  
    printf("Enter year of creation: ");
    scanf("%d", &car.year);
  
    printf("Enter the Price: ");
    scanf("%d", &car.price);
  
  } while (!checkCarInfo(car));

  FILE *fcreate = NULL;

  char fileName[64] = "";
  strcat(fileName, car.brand);
  strcat(fileName, "-");
  strcat(fileName, car.model);
  strcat(fileName, ".txt");

  //printf("%d", access(fileName, F_OK));
  while (access(fileName, F_OK) == 0) {
    printf("there is a car with the same brand and model so enter another\n");
    printf("Enter the Brand: ");
    scanf(" %19s", car.brand);
  
    printf("Enteer the Model: ");
    scanf(" %19s", car.model);

    strcpy(fileName, "");
    strcat(fileName, car.brand);
    strcat(fileName, "-");
    strcat(fileName, car.model);
    strcat(fileName, ".txt");

    if (access(fileName, F_OK) && !checkCarInfo(car)) {
      break;
    }
  }
  fcreate =  fopen(fileName, "w");
  
  fprintf(fcreate, "Brand: %s\n", car.brand);
  fprintf(fcreate, "Model: %s\n", car.model);
  fprintf(fcreate, "Color: %s\n", car.color);
  fprintf(fcreate, "Year: %d\n", car.year);
  fprintf(fcreate, "Price: %d$", car.price);

  fclose(fcreate);
}

bool checkCarInfo(Car car) {

  for (int i = 0; i < strlen(car.brand); i++) {
    // if brand[i] not a character return false
    if (!isalpha(car.brand[i])) {
      return false;
    }
  }

  for (int i = 0; i < strlen(car.model); i++) {
    // if model[i] not a character return false
    if (!isalpha(car.model[i])) {
      return false;
    }
  }

  for (int i = 0; i < strlen(car.color); i++) {
    // if color[i] not a character return false
    if (!isalpha(car.color[i])) {
      return false;
    }
  }

  if (!(car.year > 1900)) {
    return false;
  }

  if (!(car.price > 0)) {
    return false;
  }

  return true;
}

// case 2
void case2() {
  Car car;
  
  printf("Enter the Brand: ");
  scanf(" %19s", car.brand);
  
  printf("Enteer the Model: ");
  scanf(" %19s", car.model);
  
  FILE *fgetInfo = NULL;

  char fileName[64] = "", fileData[100];
  strcat(fileName, car.brand);
  strcat(fileName, "-");
  strcat(fileName, car.model);
  strcat(fileName, ".txt");

  fgetInfo =  fopen(fileName, "r");
  if (fgetInfo != NULL) {
    while (fgets(fileData, sizeof(fileData), fgetInfo)) {
      printf("%s", fileData);
    }
    printf("\n\n\n");
  }
  else {
    printf("\n\n\nCheck your data\n\n\n");
  }
  fclose(fgetInfo);
}

// case3
void case3() {
  Car car, carUpdate = {"", "", "", 0, 0};
  
  printf("Enter the Brand: ");
  scanf(" %19s", car.brand);
  
  printf("Enteer the Model: ");
  scanf(" %19s", car.model);

  
  FILE *fupdateInfo = NULL;

  char fileName[64] = "", fileData[100];
  strcat(fileName, car.brand);
  strcat(fileName, "-");
  strcat(fileName, car.model);
  strcat(fileName, ".txt");

  fupdateInfo =  fopen(fileName, "r");
  
  if (fupdateInfo != NULL) {
    
    short loopTime = 0;
    
    while (fgets(fileData, sizeof(fileData), fupdateInfo)) {
      //printf("%s", fileData);
      handleFileData(loopTime, fileData, &carUpdate);
      loopTime++;
    }
    //printf("%s, %s, %s, %d, %d", carUpdate.brand, carUpdate.model, carUpdate.color, carUpdate.year, carUpdate.price);
    printf("Brand: %s\n", carUpdate.brand);
    printf("Model: %s\n", carUpdate.model);
    printf("Color: %s\n", carUpdate.color);
    printf("Year: %d\n", carUpdate.year);
    printf("Price: %d$\n", carUpdate.price);
    printf("\n");
    fclose(fupdateInfo);
    
    fupdateInfo = fopen(fileName, "w");

    do {
      printf("Enter the Brand: ");
      scanf(" %19s", carUpdate.brand);
    
      printf("Enteer the Model: ");
      scanf(" %19s", carUpdate.model);
    
      printf("Enteer the Color: ");
      scanf(" %19s", carUpdate.color);
    
      printf("Enter year of creation: ");
      scanf("%d", &carUpdate.year);
    
      printf("Enter the Price: ");
      scanf("%d", &carUpdate.price);
    
    } while (!checkCarInfo(carUpdate));

    fprintf(fupdateInfo, "Brand: %s\n", carUpdate.brand);
    fprintf(fupdateInfo, "Model: %s\n", carUpdate.model);
    fprintf(fupdateInfo, "Color: %s\n", carUpdate.color);
    fprintf(fupdateInfo, "Year: %d\n", carUpdate.year);
    fprintf(fupdateInfo, "Price: %d$", carUpdate.price);
  }
  else {
    printf("\n\n\nCheck your data\n\n\n");
  }
  fclose(fupdateInfo);
}

void handleFileData(short loop, char *fileData, Car *car) {

  bool isSpace = false;
  short index = 0;
  
  switch (loop) {
    case 0:
      {
        for (int i = 0; fileData[i] != '\n'; i++) {
          if (isSpace) {
            car->brand[index++] = fileData[i];
          }
          else if (fileData[i] == ' ') {
            isSpace = true;
          }
        }
      }
    break;
    case 1:
      {        
        for (int i = 0; fileData[i] != '\n'; i++) {
          if (isSpace) {
            car->model[index++] = fileData[i];
          }
          else if (fileData[i] == ' ') {
            isSpace = true;
          }
        }
        
      }
    break;
    case 2:
      {
        for (int i = 0; fileData[i] != '\n'; i++) {
          if (isSpace) {
            car->color[index++] = fileData[i];
          }
          else if (fileData[i] == ' ') {
            isSpace = true;
          }
        }
      }
    break;
    case 3:
      {
        char Year[10] = "";
        for (int i = 0; fileData[i] != '\n'; i++) {
          if (isSpace) {
            Year[index++] = fileData[i];
          }
          else if (fileData[i] == ' ') {
            isSpace = true;
          }
        }
        car->year =  atoi(Year);
      }
    break;
    case 4:
      {
        char Price[10] = "";
        for (int i = 0; fileData[i] != '\n'; i++) {
          if (isSpace) {
            Price[index++] = fileData[i];
          }
          else if (fileData[i] == ' ') {
            isSpace = true;
          }
        }
        car->price =  atoi(Price);
      }
    break;
  }
}

// case 4
void case4() {
  Car car;
  
  printf("Enter the Brand: ");
  scanf(" %19s", car.brand);
  
  printf("Enteer the Model: ");
  scanf(" %19s", car.model);

  char fileName[64] = "", fileData[100];
  strcat(fileName, car.brand);
  strcat(fileName, "-");
  strcat(fileName, car.model);
  strcat(fileName, ".txt");

  if (remove(fileName) == 0) {
    printf("File successfully deleted\n\n\n");
    return;
  }
  perror("\n\n\nError deleting file\n\n\n");
}

void case5() {
  char oldName[100]="", newName[100]="";

  printf("Enter your old brand and model: ");
  scanf(" %99[^\n]s", oldName);

  for (int i = 0; oldName[i] != '\0'; i++) {
    if (oldName[i] == ' ') {
      oldName[i] = '-';
      break;
    }
    if (i == strlen(oldName)-1) {
      printf("Error renaming file\n");
      return;
    }
  }

  printf("Enter your old brand and model: ");
  scanf(" %99[^\n]s", newName);

  for (int i = 0; newName[i] != '\0'; i++) {
    if (newName[i] == ' ') {
      newName[i] = '-';
      break;
    }
    if (i == strlen(newName)-1) {
      printf("Error renaming file\n");
      return;
    }
  }

  strcat(oldName, ".txt");
  strcat(newName, ".txt");

  if (rename(oldName , newName) == 0) {
    printf("File successfully renamed\n");
  }
  else {
    printf("Error renaming file\n");
  }
}
