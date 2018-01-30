

#define MAX_FILENMAE_LEN 255
typedef struct {
	char aster;
	int  file_id;
	int  finished;	// 0: not 1: ok 2: error
	char filename[MAX_FILENMAE_LEN + 1];
} file_store_t;
struct zc_user_control{
	void *handle;
	file_store_t *capfile;
	int aster;
};

typedef enum {
	TCPDUMP_CAPTURE_ID,
	RAW_SOCKET_CAPTURE_ID,
	MAX_CAPTURE_ID
} EM_CAPTURE_T;	

static captor_t *captors[MAX_CAPTURE_ID] = {
	[TCPDUMP_CAPTURE_ID] = &tcpdump_captor,
	[RAW_SOCKET_CAPTURE_ID] = &raw_socket_captor
};

int search_captor(char *name)
{
	int idx = 0;
	for (idx = 0; idx < MAX_CAPTURE_ID; idx++) {
		if (strcasecmp(name, captors[idx]->name) == 0) {
			break;
		}
	}

	return (idx < MAX_CAPTURE_ID ? idx : -1);
}

struct zc_user_control* zc_usr_init(int file_num, long files_ptr)
{
	file_store_t *capfile;
	char **argv = (char **)files_ptr;
	struct zc_user_control *z = malloc(sizeof(struct zc_user_control));
	int captor_type = search_captor("tcpdump");
	z->handle = init_captor(captor_type, file_num, argv);
	z->capfile=(file_store_t*)(((captor_desc_t*)(z->handle))->handle);
	return z;
}