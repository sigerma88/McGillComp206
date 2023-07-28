// Structure used to store and buffer the records
struct PHONE_NODE
{
        char name[50];
        char birthdate[12];
        char phone[15];
	struct PHONE_NODE *next;
};

// External global variable
extern struct PHONE_NODE *phonebookHead;

// Function prototypes
int loadCSV();
int saveCSV();
int addRecord(char *name, char *birthdate, char *phone);
struct PHONE_NODE * findRecord(char *name);
int listRecords();
int delete(char *person);
int clear();
