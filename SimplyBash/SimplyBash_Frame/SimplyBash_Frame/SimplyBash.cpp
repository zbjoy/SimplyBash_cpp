#include "SimplyBash.h"
#include <unistd.h>
#include <string.h>

SimplyBash* SimplyBash::sb_pointer = NULL;
std::string SimplyBash::cmd;
char* SimplyBash::buf = NULL;
size_t SimplyBash::sb_buffer_size = 0;

/* 框架的启动 */
void SimplyBash::Bash_Run()
{
	sb_pointer->Init();
	while (true)
	{
		//std::cout << "Prompt start" << std::endl;
		Prompt();
		//std::cout << "Prompt end" << std::endl;
		Handler* handler = sb_pointer->Parse(cmd);
		if (handler != NULL)
		{
			handler->ProcFunc(cmd);
		}
	}
}

/* 将子类的用户创建的bash赋给SimplyBash框架 */
void SimplyBash::Set_Bash(SimplyBash* s = NULL)
{
	//std::cout << "sb_pointer start" << std::endl;
	sb_pointer = s;
	//std::cout << "sb_pointer end" << std::endl;
	sb_buffer_size = sb_pointer->GetBufferSize();
	if (buf != NULL)
	{
		delete[] buf;
		buf = NULL;
	}
	buf = new char[sizeof(char) * sb_buffer_size];
	memset(buf, 0, sb_buffer_size);

}

SimplyBash::SimplyBash()
{
}

SimplyBash::~SimplyBash()
{
	//if (buf != NULL)
	//{
	//	delete[] buf;
	//	buf = NULL;
	//}
}

/* 给出提示符 */
void SimplyBash::Prompt()
{
	cmd = "";
	memset(buf, 0, sizeof(char) * sb_buffer_size);
	write(STDOUT_FILENO, ">>>", sizeof(">>>"));
	read(STDIN_FILENO, buf, sizeof(char) * sb_buffer_size);
	if (strcmp(buf, "\n"))
	{
		buf[strlen(buf) - 1] = 0;
	}

	cmd = std::string(buf, strlen(buf));
}
