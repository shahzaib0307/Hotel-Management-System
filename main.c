#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define totalfloors 4
#define roomsonfloor 4

int checkUser(char name[], char password[]){
    FILE *users = fopen("records.txt", "r");

    if(users == NULL){
        printf("Error Occured");
    }
    else{
        char name_in[20];
        char pass_in[8];

        while(fgets(name_in, sizeof(name_in), users) != NULL ){
        	
        	name_in[strcspn(name_in, "\n")] = '\0';  // replaces \n with \0 to mark the end of name
            fgets(pass_in, sizeof(pass_in)+1, users);
            pass_in[strcspn(pass_in, "\n")] = '\0'; // replaces \n with \0 to mark the end of password
            
            if(strcmp(name, name_in)==0){
                if(strcmp(password, pass_in)==0){
                    printf("Logged in successfully!\n");
                    fclose(users);
                    return 1;
                }else{	
                    printf("Incorrect Password\n");
					return 0;
                }
            }
        }
		printf("User not found\n");
		fclose(users);
		return 0;
    }
};

int createUser(char name[], char password[]){
	FILE *users = fopen("records.txt", "r");
	char file_name[30];
	if(users == NULL){
		printf("Error Occured\n");
		return 0;
	}else{
		char name_in[20];
		char pass_in[8];
		while(fgets(name_in, sizeof(name_in), users) != NULL){
			if(strcmp(name, name_in)==0){
				printf("Username already exists!\n");
				fclose(users);
				return 0;
			}
			fgets(pass_in, sizeof(pass_in), users);
		}
		FILE *user = fopen("records.txt", "a");
		if(user == NULL){
			printf("Error Occured\n");
			return 0;
		}else{
			fputs(name, user);
			fputs(password, user);
			fclose(user);
		}

		return 1;
	}
}

void availableRooms(){
	FILE *rooms = fopen("roombooking.txt", "r");
	if(rooms == NULL){
		printf("Error Occured\n");
	}else{
		char room;
		char type[4][10] = {"Deluxe", "Premium", "Normal", "Shared"};
		int floor_count = 0; 
		int room_count = 0;
		while(fscanf(rooms, "%c", &room) != EOF){
			if(room == '0'){
				printf("%s Room %d\n", type[floor_count], room_count+1);
			}
			room_count++;
			if(room == '\n'){
				room_count = 0;
				floor_count++;
			}
		}
		fclose(rooms);
	}
};

int bookRoom(int floor, int room, char name[], int days){
	char rooms_arr[totalfloors][roomsonfloor+1];
	char type[4] = {'D', 'P', 'N', 'S'};
	int rates[4] = {10000, 7000, 4000, 2000};
	char file_name[30];

	FILE *rooms = fopen("roombooking.txt", "r");
	if(rooms == NULL){
		printf("Error Occured!");
		return 0;
	}else{
		for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                fscanf(rooms, "%c", &rooms_arr[i][j]);
            }
        }
        fclose(rooms);
		if(rooms_arr[floor][room]=='1'){
			printf("Room Already Occupied!\n");
			return 0;
		}
		rooms_arr[floor][room] = '1';
	}
	FILE *rooms_new = fopen("roombooking.txt", "w");
	if(rooms == NULL){
		printf("Error Occured!");
		return 0;
	}else{
		for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                fprintf(rooms_new, "%c", rooms_arr[i][j]);
            }
        }
        fclose(rooms);
	}
	
	FILE *hotel_file = fopen("hotelrecord.txt", "a");
	if(hotel_file == NULL){
		printf("Error Occured!");
		return 0;
	}else{
		fprintf(hotel_file, "%s %c %d %d %d %d\n", name, type[floor], room+1, days, days*rates[floor], 0);
		fclose(hotel_file);
	}

	
	printf("Room Booked Successfully!\n");
	return 1;
	

};

void changeRoom(char name[], char password[], int floor, int room, int days){

	char type[4] = {'D', 'P', 'N', 'S'};
	int rates[4] = {10000, 7000, 4000, 2000};

	name[strcspn(name, "\n")] = '\0';
	struct hotel{
		char name[20];
		char type;
		int room;
		int days;
		int total;
		int food;
	};
	struct hotel h;
	//reading records from hotelrecord.txt until username is found
	FILE *records = fopen("hotelrecord.txt", "r");
	if(records == NULL){
		printf("Error Occured");
	}else{
		
		while(fscanf(records, "%s %c %d %d %d %d", &h.name, &h.type, &h.room, &h.days, &h.total, &h.food) != EOF){
			if(strcmp(h.name, name) == 0){
				break;
			}
		}
		fclose(records);
	}

	//updating roombooking.txt
	FILE *rooms = fopen("roombooking.txt", "r");
	if(rooms == NULL){
		printf("Error Occured!");
	}else{
		char rooms_arr[totalfloors][roomsonfloor+1];
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 5; j++) {
				fscanf(rooms, "%c", &rooms_arr[i][j]);
			}
		}
		fclose(rooms);
		if(rooms_arr[floor][room] == '1'){
			printf("Room is already booked!\n");
			return;
		}else{
			rooms_arr[floor][room] = '1';
			if (h.type == 'D') {
				rooms_arr[0][h.room-1] = '0';
			} else if (h.type == 'P') {
				rooms_arr[1][h.room-1] = '0';
			} else if (h.type == 'N') {
				rooms_arr[2][h.room-1] = '0';
			} else if (h.type == 'S') {
				rooms_arr[3][h.room-1] = '0';
			}
		}
		FILE *rooms_new = fopen("roombooking.txt", "w");
		if(rooms == NULL){
			printf("Error Occured!");
			return;
		}else{
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 5; j++) {
					fprintf(rooms_new, "%c", rooms_arr[i][j]);
				}
			}
			fclose(rooms);
		}
	}

	//updating hotelrecord.txt
	FILE *hotel_file = fopen("hotelrecord.txt", "r");
	if(hotel_file == NULL){
		printf("Error Occured!");
		return;
	}else{
		FILE *hotel_file_new = fopen("hotelrecord.txt", "r+");
		if(hotel_file_new == NULL){
			printf("Error Occured!");
			return;
		}else{
			while(fscanf(hotel_file, "%s %c %d %d %d", &h.name, &h.type, &h.room, &h.days, &h.total, &h.food) != EOF){
				// if username is found, update the category, room number, days and total
				if(strcmp(h.name, name) == 0){
					fprintf(hotel_file_new, "%s %c %d %d %d\n", h.name, type[floor], room+1, days, days*rates[floor], h.food);
				// if username is not found, write the record as it is
				}else{
					fprintf(hotel_file_new, "%s %c %d %d %d\n", h.name, h.type, h.room, h.days, h.total, h.food);
				}
			}
			fclose(hotel_file);
			fclose(hotel_file_new);
		}
	}
	
}

void foododering(char name[])
{
	name[strcspn(name, "\n")] = '\0';
    char file_name[30];
    int foodbooking=0;
    int numberofdays=0;
    int foodtotal=0;
    printf("------------------------------------------------\n");
    printf("             We have three deal of food:        \n");
    printf("------------------------------------------------\n");

    printf("------------------------------------------------\n");
    printf("                Deal 1: price 5000             \n");
    printf("------------------------------------------------\n");
    printf("1 -> Veg Manchurian\n");
    printf("2 -> Mutton Fry\n");
    printf("4 -> Shawarma Roll\n");
    printf("5 -> Fish Fry\n");

    printf("------------------------------------------------\n");
    printf("                Deal 2: price 6000             \n");
    printf("------------------------------------------------\n");
    printf("1 -> Handi\n");
    printf("2 -> Malai Boti\n");
    printf("4 -> Kabab\n");
    printf("5 -> Prawns\n");

    printf("------------------------------------------------\n");
    printf("                Deal 3: price 8000             \n");
    printf("------------------------------------------------\n");
    printf("1 -> Handi(Makhni)\n");
    printf("2 -> Mutton Boti Fry\n");
    printf("4 -> Ginger Chicken\n");
    printf("5 -> Mushroom Gravy\n");

    printf("press one for deal one and +1 for other:");
    scanf("%d",&foodbooking);

    printf("how many days of food you want:");
    scanf("%d",&numberofdays);

    if(foodbooking==1){
        foodtotal=numberofdays*5000;
    }
    else if(foodbooking==2){
        foodtotal=numberofdays*6000;
    }
    else if(foodbooking==3){
        foodtotal=numberofdays*8000;
    }else{
		printf("invalid input");
		return;
	}

	FILE *hotel_file = fopen("hotelrecord.txt", "r");
	if(hotel_file == NULL){
		printf("Error Occured!");
		return;
	}else{
		FILE *hotel_file_new = fopen("hotelrecord.txt", "r+");
		if(hotel_file_new == NULL){
			printf("Error Occured!");
			return;
		}else{
			struct hotel{
				char name[20];
				char type;
				int room;
				int days;
				int total;
				int food;
			};
			struct hotel h;
			while(fscanf(hotel_file, "%s %c %d %d %d %d", &h.name, &h.type, &h.room, &h.days, &h.total, &h.food) != EOF){
				if(strcmp(h.name, name) == 0){
					fprintf(hotel_file_new, "%s %c %d %d %d %d\n", h.name, h.type, h.room, h.days, h.total, h.food+foodtotal);
				}else{
					fprintf(hotel_file_new, "%s %c %d %d %d %d\n", h.name, h.type, h.room, h.days, h.total, h.food);
				}
			}
			fclose(hotel_file);
			fclose(hotel_file_new);
		}
	}
	printf("Food Ordered Successfully!\n");
}

void checkOut(char name[]){
	char type[4] = {'D', 'P', 'N', 'S'};
	int rates[4] = {10000, 7000, 4000, 2000};

	name[strcspn(name, "\n")] = '\0';
	struct hotel{
		char name[20];
		char type;
		int room;
		int days;
		int total;
		int food;
	};
	struct hotel h;
	//reading records from hotelrecord.txt until username is found
	FILE *records = fopen("hotelrecord.txt", "r");
	if(records == NULL){
		printf("Error Occured");
	}else{
		
		while(fscanf(records, "%s %c %d %d %d %d", &h.name, &h.type, &h.room, &h.days, &h.total, &h.food) != EOF){
			if(strcmp(h.name, name) == 0){
				break;
			}
		}
		fclose(records);
	}

	//updating roombooking.txt
	FILE *rooms = fopen("roombooking.txt", "r");
	if(rooms == NULL){
		printf("Error Occured!");
	}else{
		char rooms_arr[totalfloors][roomsonfloor+1];
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 5; j++) {
				fscanf(rooms, "%c", &rooms_arr[i][j]);
			}
		}
		fclose(rooms);
		if (h.type == 'D') {
			rooms_arr[0][h.room-1] = '0';
		} else if (h.type == 'P') {
			rooms_arr[1][h.room-1] = '0';
		} else if (h.type == 'N') {
			rooms_arr[2][h.room-1] = '0';
		} else if (h.type == 'S') {
			rooms_arr[3][h.room-1] = '0';
		}		
		FILE *rooms_new = fopen("roombooking.txt", "w");
		if(rooms == NULL){
			printf("Error Occured!");
			return;
		}else{
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 5; j++) {
					fprintf(rooms_new, "%c", rooms_arr[i][j]);
				}
			}
			fclose(rooms);
		}
	}

	int flag=0;

	//updating hotelrecord.txt
	FILE *hotel_file = fopen("hotelrecord.txt", "r");
	if(hotel_file == NULL){
		printf("Error Occured!");
		return;
	}else{
		FILE *hotel_file_new = fopen("temp.txt", "w");
		if(hotel_file_new == NULL){
			printf("Error Occured!");
			return;
		}else{
			while(fscanf(hotel_file, "%s %c %d %d %d %d", &h.name, &h.type, &h.room, &h.days, &h.total, &h.food) != EOF){
				// if username is found, print the bill
				if(strcmp(h.name, name) == 0){
					printf("BILL FOR %s\n", h.name);
					printf("Room Charges: %d\n", h.total);
					printf("Food Charges: %d\n", h.food);
					printf("Total Bill: %d\n", h.total+h.food);
					printf("Thank you for staying with us!\n");
					flag = 1;
				// if username is not found, write the record as it is
				}else{
					fprintf(hotel_file_new, "%s %c %d %d %d %d\n", h.name, h.type, h.room, h.days, h.total, h.food);
				}
			}
			
			fclose(hotel_file);
			fclose(hotel_file_new);

			if(flag==0){
				printf("No room booked against this ID!\n");
				return;
			}

		}
		FILE *hotel_file_final = fopen("hotelrecord.txt", "w");
		if(hotel_file_final == NULL){
			printf("Error Occured!");
			return;
		}else{
			FILE *hotel_file_temp = fopen("temp.txt", "r");
			if(hotel_file_temp == NULL){
				printf("Error Occured!");
				return;
			}else{
				while(fscanf(hotel_file_temp, "%s %c %d %d %d %d", &h.name, &h.type, &h.room, &h.days, &h.total, &h.food) != EOF){
					fprintf(hotel_file_final, "%s %c %d %d %d %d\n", h.name, h.type, h.room, h.days, h.total, h.food);
				}
				fclose(hotel_file_temp);
				fclose(hotel_file_final);
			}
		}
	}
}

int main(){
    char name[20]; 
    char pass[8];
    int choice=0;
    int floor, room;
    
    printf("------------------------------------------------\n");
    printf("		WELCOME TO KHAN HOTEL           \n");
    printf("		Select an Option                \n");
    printf("		1. Login                        \n");
    printf("		2. Create Account               \n");
    printf("		3. Exit                         \n");
    printf("------------------------------------------------\n");
    scanf("%d", &choice);
    system("cls");

    switch(choice){
    	case 1:
    		do{
        		printf("Enter username: ");
        		scanf("%s", &name);
        		printf("Enter Password: ");
        		scanf("%s", &pass);
    		}while(checkUser(name, pass) == 0);
			system("cls");
    		break;
    	case 2:
    		do{
        		printf("Enter username: ");
        		scanf("%s", &name);
        		printf("Enter Password: ");
        		scanf("%s", &pass);
        		strcat(name, "\n");
        		strcat(pass, "\n");
    		}while(createUser(name, pass) == 0);
    		break;
			system("cls");
    
		case 3:
    		return 0;
	}
	while(1){
	
		printf("------------------------------------------------\n");
		printf("		1. Check Available Rooms                        \n");
	    printf("		2. Book A Room               \n");
	    printf("		3. Change Room                         \n");
	    printf("		4. Check Out                         \n");
	    printf("		5. Exit                         \n");
	    printf("------------------------------------------------\n");
		scanf("%d", &choice);

		switch(choice){
			case 1:
				printf("--------------------------------------\n");
				printf("          Available Rooms\n");
				printf("--------------------------------------\n");
				availableRooms();
				break;
			case 2:
				printf("------------------------------------------------\n");
				printf("		1. Delux Room                        \n");
	    		printf("		2. Premium Room               \n");
	    		printf("		3. Normal                         \n");
	    		printf("		4. Shared                         \n");
				printf("------------------------------------------------\n");
				scanf("%d", &floor);
				printf("Enter Room Number from available rooms of this category: ");
				scanf("%d", &room);
				system("cls");
				printf("How many days do you want to book the room for? ");
				scanf("%d", &choice);
				if(bookRoom(floor-1, room-1, name, choice)!=0){
					printf("Do you want to avail our in-house food deals? (1/0): ");
					scanf("%d", &choice);
					if(choice == 1){
						foododering(name);
						system("cls");
					}
				}
				break;
			case 3:
				printf("--------------------------------------\n");
				printf("          Available Rooms\n");
				printf("--------------------------------------\n");
				availableRooms();
				printf("------------------------------------------------\n");
				printf("		1. Delux Room                        \n");
	    		printf("		2. Premium Room               \n");
	    		printf("		3. Normal                         \n");
	    		printf("		4. Shared                         \n");
				printf("------------------------------------------------\n");
				scanf("%d", &floor);
				printf("Enter Room Number from available rooms of this category: ");
				scanf("%d", &room);
				system("cls");
				printf("How many days do you want to book the room for? ");
				scanf("%d", &choice);
				system("cls");
				changeRoom(name, pass, floor-1, room-1, choice);
				break;
			case 4:
				checkOut(name);
				break;
			case 5:
				return 0;	
		}
	}
}
