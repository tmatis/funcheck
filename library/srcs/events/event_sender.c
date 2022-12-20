#include <string.h>
#include "../shared_memory/shared_memory.h"

void send_event(t_shared_info *shared_memory, t_event event)
{
	shared_memory->event = event;
	sem_post(&shared_memory->lock_host);
	sem_wait(&shared_memory->lock_guest);
}

void send_event_nonblocking(t_shared_info *shared_memory, t_event event)
{
	shared_memory->event = event;
	sem_post(&shared_memory->lock_host);
}

void _send_alloc_event(
	t_shared_info *shared_memory,
	void *ptr,
	size_t size,
	const char *function_name)
{
	shared_memory->allocation.ptr = ptr;
	shared_memory->allocation.size = size;
	strncpy(
		shared_memory->function_name,
		function_name,
		sizeof(shared_memory->function_name));
	send_event(shared_memory, ALLOC);
}

void _send_remove_alloc_event(
	t_shared_info *shared_memory,
	void *ptr,
	const char *function_name)
{;
	shared_memory->allocation.ptr = ptr;
	strncpy(
		shared_memory->function_name,
		function_name,
		sizeof(shared_memory->function_name));
	send_event(shared_memory, REMOVE_ALLOC);
}

void _send_function_call_event(
	t_shared_info *shared_memory,
	const char *function_name)
{
	strncpy(
		shared_memory->function_name,
		function_name,
		sizeof(shared_memory->function_name));
	send_event(shared_memory, FUNCTION_CALL);
}