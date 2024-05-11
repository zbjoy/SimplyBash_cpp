#pragma once
#include <iostream>

class Handler;
class SimplyBash
{
protected:
	virtual void Init() = 0;
	virtual Handler* Parse(std::string _cmd) = 0;
	virtual size_t GetBufferSize() = 0;

public:
	static void Bash_Run();
	static void Set_Bash(SimplyBash* s);

protected:
	SimplyBash();
	~SimplyBash();

private:
	static void Prompt();

private:
	static size_t sb_buffer_size;
	static SimplyBash* sb_pointer;
	static std::string cmd;
	static char* buf;
};

class Handler
{
public:
	virtual void ProcFunc(std::string _cmd) = 0;
};
