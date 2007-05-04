// BCP_message_mpi.cpp is a declaration of BCP_message_mpi
// Sonya Marcarelli & Igor Vasil'ev (vil@icc.ru)
// All Rights Reserved.

#include "BcpConfig.h"
#if defined(COIN_HAS_MPI)

#include <cstdio>
#include <cmath>

#define MPICH_SKIP_MPICXX
#include <mpi.h>

#include "BCP_error.hpp"
#include "BCP_process.hpp"
#include "BCP_buffer.hpp"
#include "BCP_vector.hpp"
#include "BCP_message_mpi.hpp"

bool BCP_mpi_environment::mpi_init_called = false;

//#############################################################################

int BCP_mpi_environment::is_mpi(int argc, char *argv[])
{
    int pid;
    if (! mpi_init_called) {
	MPI_Init(&argc, &argv);
	// MPI_Init may or may not have succeeded. In any case check if we can
	// get the number of procs
	if (MPI_Comm_size(MPI_COMM_WORLD, &num_proc) != MPI_SUCCESS) {
	    // Now it's certain. Not an MPI environment
	    return -1;
	}
	mpi_init_called = true;
    }
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    return pid;
}

//#############################################################################


BCP_mpi_environment::BCP_mpi_environment(int argc, char *argv[])
{
    /* Initialize the MPI environment. */
    is_mpi(argc, argv);
}

//-----------------------------------------------------------------------------

BCP_mpi_environment::~BCP_mpi_environment()
{
    MPI_Finalize();
    mpi_init_called = false;
}

//-----------------------------------------------------------------------------

void
BCP_mpi_environment::check_error(const int code, const char* str) const
{
    if (code != MPI_SUCCESS){
	printf("%s returned error code %i.\n", str, code);
	throw BCP_fatal_error(" ERROR in mpi -- exiting.\n");
    }
}

//-----------------------------------------------------------------------------

int
BCP_mpi_environment::register_process(USER_initialize* user_init)
{
    int pid;
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    setvbuf(stdout, (char *)NULL, _IOLBF, 0);
    return pid;
}

int
BCP_mpi_environment::parent_process()
{
    int pid;
    MPI_Comm_rank(MPI_COMM_WORLD, &pid);
    if (pid == 0)
	//I am the master and I have no parent
	return -1;
    //The master process has got always pid=0
    return 0;
}

bool
BCP_mpi_environment::alive(const int pid)
{
    //In Mpi is not possible check if a process is alive
    /* FIXME */
    return true;
}

BCP_vec<int>::const_iterator
BCP_mpi_environment::alive(const BCP_proc_array& parray)
{
    //In Mpi is not possible check if a process is alive
    return parray.procs().end();
}

//-----------------------------------------------------------------------------

void
BCP_mpi_environment::send(const int target, const BCP_message_tag tag)
{
    //create an empty buffer and send it with the tag
    void * buf = NULL;
    check_error(MPI_Send(&buf, 0, MPI_CHAR,
			 target, tag, MPI_COMM_WORLD),"MPI_Send");
}

void
BCP_mpi_environment::send(const int target,
			  const BCP_message_tag tag, const BCP_buffer& buf)
{
    check_error(MPI_Send(const_cast<char*>(buf.data()), buf.size(), MPI_CHAR,
			 target, tag, MPI_COMM_WORLD),"MPI_Send");
}

//-----------------------------------------------------------------------------

void
BCP_mpi_environment::multicast(const BCP_proc_array* const target,
			       const BCP_message_tag tag)
{
    const BCP_vec<int>& pids = target->procs();
    void * buf = NULL;
    for (int i=target->size()-1; i>=0; --i) {
	check_error(MPI_Send(&buf, 0, MPI_CHAR,
			     pids[i], tag, MPI_COMM_WORLD),"MPI_Send");
    }
}

void
BCP_mpi_environment::multicast(const BCP_proc_array* const target,
			       const BCP_message_tag tag,
			       const BCP_buffer& buf)
{
    const BCP_vec<int>& pids = target->procs();
    for (int i=target->size()-1; i>=0; --i) {
	check_error(MPI_Send(const_cast<char*>(buf.data()), buf.size(),
			     MPI_CHAR, pids[i], tag, MPI_COMM_WORLD),
		    "MPI_Send");
    }
}

void
BCP_mpi_environment::multicast(BCP_vec<int>::const_iterator beg,
			       BCP_vec<int>::const_iterator end,
			       const BCP_message_tag tag)
{
    void * buf = NULL;
    for ( ; beg != end; ++beg) {
	check_error(MPI_Send(&buf, 0, MPI_CHAR,
			     *beg, tag, MPI_COMM_WORLD),"MPI_Send");
    }
}

void
BCP_mpi_environment::multicast(BCP_vec<int>::const_iterator beg,
			       BCP_vec<int>::const_iterator end,
			       const BCP_message_tag tag,
			       const BCP_buffer& buf)
{
    for ( ; beg != end; ++beg) {
	check_error(MPI_Send(const_cast<char*>(buf.data()),buf.size(),
			     MPI_CHAR, *beg, tag, MPI_COMM_WORLD),"MPI_Send");
    }
}

//-----------------------------------------------------------------------------

void
BCP_mpi_environment::receive(const int source,
			     const BCP_message_tag tag, BCP_buffer& buf,
			     const double timeout)
{
    buf.clear();
    delete buf._sender;   buf._sender = 0;
    int pid = (source == BCP_AnyProcess ? MPI_ANY_SOURCE : source);
    int msgtag = (tag == BCP_Msg_AnyMessage ? MPI_ANY_TAG : tag);
    int flag = 0;
    MPI_Status status;

    if (timeout < 0) {
	check_error(MPI_Probe(pid, msgtag, MPI_COMM_WORLD, &status),
		    "MPI_Probe");
	flag = 1;
    } else {
	check_error(MPI_Iprobe(pid, msgtag, MPI_COMM_WORLD, &flag, &status),
		    "MPI_Iprobe");
    }
    //There is no message
    if (!flag) {
	buf._msgtag = BCP_Msg_NoMessage;
	return;
    }

    int bytes;
    //Get the size of message
    check_error(MPI_Get_count( &status, MPI_CHAR, &bytes ),"MPI_Get_Count");
    buf.make_fit(bytes);
    buf._msgtag = static_cast<BCP_message_tag>(status.MPI_TAG);
    delete buf._sender;
    buf._sender = status.MPI_SOURCE;
    buf._size = bytes;

    //Receive the content of the message
    check_error(MPI_Recv(buf._data, bytes, MPI_CHAR,
			 pid, msgtag, MPI_COMM_WORLD, &status),"MPI_Recv");
}



//-----------------------------------------------------------------------------

bool
BCP_mpi_environment::probe(const int source, const BCP_message_tag tag)
{
    MPI_Status  status;
    // MPI_Request request;
    int  flag = 0;
    int pid = (source == BCP_AnyProcess ? MPI_ANY_SOURCE : source);
    int msgtag = (tag == BCP_Msg_AnyMessage ? MPI_ANY_TAG : tag);
    check_error(MPI_Iprobe(pid, msgtag, MPI_COMM_WORLD, &flag, &status),
		"MPI_Iprobe");
    return flag > 0;
}

//-----------------------------------------------------------------------------

int
BCP_mpi_environment::start_process(const BCP_string& exe, const bool debug)
{
#ifdef COIN_HAS_MPI2
    printf("Sorry, MPI2 process spawning is not supported yet...\n");
    abort();
#else
    printf("Sorry, MPI1 does not support process spawning...\n");
    abort();
#endif
}

int
BCP_mpi_environment::start_process(const BCP_string& exe,
				   const BCP_string& machine,
				   const bool debug)
{
#ifdef COIN_HAS_MPI2
    printf("Sorry, MPI2 process spawning is not supported yet...\n");
    abort();
#else
    printf("Sorry, MPI1 does not support process spawning...\n");
    abort();
#endif
}

BCP_proc_array*
BCP_mpi_environment::start_processes(const BCP_string& exe,
				     const int proc_num,
				     const bool debug)
{
#ifdef COIN_HAS_MPI2
    printf("Sorry, MPI2 process spawning is not supported yet...\n");
    abort();
#else
    printf("Sorry, MPI1 does not support process spawning...\n");
    abort();
#endif
}

BCP_proc_array*
BCP_mpi_environment::start_processes(const BCP_string& exe,
				     const int proc_num,
				     const BCP_vec<BCP_string>& machines,
				     const bool debug)
{
#ifdef COIN_HAS_MPI2
    printf("Sorry, MPI2 process spawning is not supported yet...\n");
    abort();
#else
    printf("Sorry, MPI1 does not support process spawning...\n");
    abort();
#endif
}

#endif /* COIN_HAS_MPI */
