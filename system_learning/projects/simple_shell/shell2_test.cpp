#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
const int MAX_ARG = 8; // ÿ�����������7������
const int MAX = 1024;
const int MAX_CMD = 16; // �ܵ������16������
// #pragma warning(disable : 4996)

struct cmd {
	char* argv[MAX_ARG];
	char* in, * out;
};
void output(cmd head[], int num) {
	using std::cout;
	using std::endl;
	for (int i = 0; i < num; i++) {
		cout << "cmd-show:" << head[i].argv[0] << ", ";
		for (int j = 1; head[i].argv[j]; j++) {
			cout << "argv:" << head[i].argv[j] << ", ";
		}
		cout << "in: ";
		if (head[i].in == nullptr)
			cout << "NULL" << ", ";
		else
			cout << head[i].in << ", ";
		cout << "out: ";
		if (head[i].out == nullptr)
			cout << "NULL" << endl;
		else
			cout << head[i].out << endl;
	}
}
int destru_cmd(char* buf, cmd* head) {
	int cmd_num = 0;
	char* tmp_buf = buf;
	char* tmp_str = std::strtok(tmp_buf, "|");
	while (tmp_str != nullptr) {
		head[cmd_num++].argv[0] = tmp_str;
		tmp_str = std::strtok(NULL, "|");
	}
	for (int i = 0; i < cmd_num; i++) {
		char* cur_cmd = head[i].argv[0];
		head[i].in = nullptr;
		head[i].out = nullptr;
		int argc_num = 0;
		while (*cur_cmd) { // ÿ��ֻ����һ���ַ�
			if (*cur_cmd == ' ') { // ���ո��滻Ϊ\0�ַ�����ֹ��־
				*cur_cmd++ = '\0';
				continue;
			}
			if (*cur_cmd == '<') {
				// ��һ�������ַ�
				*cur_cmd = '\0';
				while (*(++cur_cmd) == ' ');
				head[i].in = cur_cmd; // �׸��ǿո��ַ���ַ��Ϊ�ض������ļ����ַ����׵�ַ
				if (*cur_cmd == '\0') // ����ض�����������ݣ�����
				{
					std::cout << "�ض������\n";
					return -1;
				}
			}
			if (*cur_cmd == '>') {
				// ��һ�������ַ�
				*cur_cmd = '\0';
				while (*(++cur_cmd) == ' ');
				head[i].out = cur_cmd;
				if (*cur_cmd == '\0') // ����ض�����������ݣ�����
				{
					std::cout << "�ض������\n";
					return -1;
				}
			}
			// �����ǰ�ַ��ǿո������Ǹ�����ĵ�һ���ַ�������ǰһ���ַ���'\0'����ô
			// ��ǰ�ַ���ַ��Ϊĳ��������ַ
			if (*cur_cmd != ' ' && (cur_cmd == head[i].argv[0] || *(cur_cmd - 1) == '\0')) {
				head[i].argv[argc_num++] = cur_cmd;
			}
			cur_cmd++;
		}
		head[i].argv[argc_num] = NULL;
	}
	return cmd_num;
}
void test01() {
	using namespace std;
	while (1) {
		char buf[MAX];
		cmd head[MAX_CMD];
		cout << "shell%% ";
		cin.getline(buf, MAX);
		
		if (!strcmp(buf, "exit") || !strcmp(buf, "quit") ||
			!strcmp(buf, "EXIT") || !strcmp(buf, "bye"))
			break;
		// cout << "buf = " << buf << endl;
		// while (cin.get() != '\n')
		//	continue;
		int cmd_num = destru_cmd(buf, head);
		output(head, cmd_num);
		// �����������������̣�ÿ������ִ��һ������
		int i;
		for (i = 0; i < cmd_num; i++) {
			pid_t pid = fork();
			if (pid == 0)
				break;
			else if (pid == -1) {
				perror("fork failed\n");
				exit(1);
			}
		}
		if (i < cmd_num) {// �ӽ���ִ������
			
			if (head[i].in){// �ж������ض������
				int fd = open(head[i].in, O_RDONLY | O_CREAT| O_TRUNC, 0664);
				dup2(fd, STDIN_FILENO);
			}
			if (head[i].out) {
				int fd = open(head[i].out, O_WRONLY | O_CREAT| O_TRUNC, 0664);
				dup2(fd, STDOUT_FILENO);
			}
			execvp(head[i].argv[0], head[i].argv); 

		}else { // �����̻����ӽ���
			for (int i = 0; i < cmd_num; i++)
				wait(NULL);
		}
	}
}
int main() {
	test01();
	return 0;
}
