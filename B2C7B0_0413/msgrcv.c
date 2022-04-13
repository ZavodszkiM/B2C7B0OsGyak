#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#define MSGKEY 654321L

struct msgbuf1 {
	long tipus;
	char mtext[512];
} rcvbuf, *msgp;

struct msqid_ds ds, *buf;

int main()
{
	int msgid;
	key_t kulcs;
	int tipus, msgflg;
	int rtn, meret;

	kulcs = MSGKEY;
	msgflg = 00666 | IPC_CREAT | MSG_NOERROR;

	msgid = msgget(kulcs, msgflg);
 	if ( msgid == -1) {
                perror("\n Az msgget rendszerhívás sikertelen!");
                exit(-1);
        }
	printf("\n Az üzenet ID: %d",msgid);

	msgp = &rcvbuf;
	buf = &ds;
	meret = 20;
	tipus = 0;
	rtn = msgctl(msgid,IPC_STAT,buf);
	printf("\n Az uzenetek szama: %ld",buf->msg_qnum);

	while (buf->msg_qnum) {


	rtn = msgrcv(msgid,(struct msgbuf *)msgp, meret, tipus, msgflg);
	printf("\n Visszatérés: %d, A fogadott üzenet:%s\n",rtn, msgp->mtext);
	rtn = msgctl(msgid,IPC_STAT,buf);

}
	exit (0);
}
