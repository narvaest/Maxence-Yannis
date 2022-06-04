typedef struct{
	char* title;
	char* writer; 
	int number;
	char* category;
	int available;
}Book;

typedef struct{
	char* login;
	char* password;
	int type;
	int borrow[5];
}Username;
