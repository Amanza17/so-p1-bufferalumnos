enum {
	Maxspace = 65,
};

struct Student {
	char name[Maxspace];
	char surname[Maxspace];
	int mark;
};

typedef struct Student Student;

struct Buf {
	Student **arr;
	int size;
};

typedef struct Buf Buf;

Buf *bookSpace(int);
int add(Buf *, Student *);
int print(Buf *);
int freeBuf(Buf *);
int delStudent(Buf *, char *, char *);
Student *extractHigherMark(Buf *);
Student *extractLowerMark(Buf *);
Student *extractStudent(Buf *, char *, char *);
