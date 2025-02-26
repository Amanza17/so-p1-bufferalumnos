enum {
	Maxspace = 65,
};

struct Student {
	char name[Maxspace];
	char surname[Maxspace];
	int mark;
};

typedef struct Student Student;

struct Buffer {
	Student **arr;
	int size;
};

typedef struct Buffer Buffer;

Buffer *bookSpace(int);
int add(Buffer *, Student *);
int print(Buffer *);
int freeBuffer(Buffer *);
int delStudent(Buffer *, char *, char *);
Student *extractHigherMark(Buffer *);
Student *extractLowerMark(Buffer *);
Student *extractStudent(Buffer *, char *, char *);
