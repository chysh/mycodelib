#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONFIG_FILENAME "./config.ini"

char db_ip[32] = {0};
char db_name[32] = {0};
int dump_period = 1;
char lib_switch = 0;

typedef struct
{
    char *name;
    int type;
#define TYPE_LONG 1
#define TYPE_ULONG 2
#define TYPE_STR 3
#define TYPE_CHAR 4
#define TYPE_YN 5
#define TYPE_INT16 6
#define TYPE_INT32 7
    void *value;
    int size;
} name_value_t;

static name_value_t conf_table[] = {
    {"mysql_ip", TYPE_STR, db_ip, 0},
    {"db_name", TYPE_STR, db_name, 0},
    {"dump_thing", TYPE_INT32, &dump_period, 0},
    {"some_switch", TYPE_YN, &lib_switch, 0},
};

static int read_local_config(void)
{
    char buff[128], *pbuf = NULL;
    char buf[64];
    int idx = 0, i, ret = 0;
    FILE *rule_file = open(CONFIG_FILENAME, "r");
    if (!rule_file)
    {
        printf("open %s error");
        return -1;
    }
    while (memset(buff, 0, sizeof(buff)) && fgets(buff, 64, rule_file))
    {
        pbuf = strchr(buff, '=');
        if (pbuf == NULL)
            continue;
        pbuf++;
        for (idx = 0; idx < sizeof(conf_table) / sizeof(conf_table[0]); idx++)
        {
            if (strncasecmp(buff, conf_table[idx].name, strlen(conf_table[idx].name)) == 0)
            {
                while (*pbuf == ' ' || *pbuf == '\t')
                {
                    pbuf++;
                }
                for (i = strlen(pbuf) - 1; i >= 0; i--)
                {
                    if (pbuf[i] == '\r' || pbuf[i] == '\n')
                        pbuf[i] = 0;
                }
                if (*pbuf != '\0')
                {
                    if (conf_table[idx].type == TYPE_LONG)
                        *(long *)(conf_table[idx].value) = atoi(pbuf);
                    else if (conf_table[idx].type == TYPE_STR)
                        strcpy((char *)(conf_table[idx].value), pbuf);
                    else if (conf_table[idx].type == TYPE_CHAR)
                        *(char *)(conf_table[idx].value) = pbuf[0];
                    else if (conf_table[idx].type == TYPE_YN)
                        *(char *)(conf_table[idx].value) = (pbuf[0] == 'y' || pbuf[0] == 'Y') ? 1 : 0;
                    else if (conf_table[idx].type == TYPE_ULONG)
                        *(unsigned long *)(conf_table[idx].value) = atoi(pbuf);
                    else if (conf_table[idx].type == TYPE_INT32)
                        *(int *)(conf_table[idx].value) = atoi(pbuf);
                }
                break;
            }
        }
    }
    if (rule_file) fclose(rule_file);
    return 1;
}