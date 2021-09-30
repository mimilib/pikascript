/* this demo shows the usage of method */
#include "PikaStdLib_SysObj.h"
#include <stdio.h>

void obj_runWithInfo(PikaObj *self, char *cmd)
{
    printf(">>> %s\r\n", cmd);
    obj_run(self, cmd);
}

int main()
{
    /* new root object */
    PikaObj *root = newRootObj("root", New_PikaStdLib_SysObj);

    obj_runWithInfo(root, "set('a',1)");
    obj_runWithInfo(root, "print(a)");
    obj_runWithInfo(root, "type('a')");
    obj_runWithInfo(root, "remove('a')");

    obj_runWithInfo(root, "set('a','test')");
    obj_runWithInfo(root, "print(a)");
    obj_runWithInfo(root, "type('a')");
    obj_runWithInfo(root, "remove('a')");

    obj_runWithInfo(root, "set('a',1)");
    obj_runWithInfo(root, "set('b',a)");
    obj_runWithInfo(root, "print(b)");
    obj_runWithInfo(root, "remove('a')");
    obj_runWithInfo(root, "remove('b')");

    printf("memory used max = %0.2f kB\r\n", pikaMemMax() / 1024.0);
    printf("memory used now = %0.2f kB\r\n", pikaMemNow() / 1024.0);

    printf(">>> ");
    /* user input buff */
    char inputBuff[256] = {0};
    /* run the script with check*/
    while (1)
    {
        /* get user input */
        fgets(inputBuff, sizeof(inputBuff), stdin);

        /* run PikaScript and get res */
        Args *resArgs = obj_runDirect(root, inputBuff);

        /* get system output of PikaScript*/
        char *sysOut = args_getSysOut(resArgs);
        ;

        if (!strEqu("", sysOut))
        {
            /* print out the system output */
            printf("%s\r\n", sysOut);
        }
        printf(">>> ");

        /* deinit the res */
        args_deinit(resArgs);
    }
}
