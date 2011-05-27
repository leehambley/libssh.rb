#ifndef LIBSSHRB_H
#define LIBSSHRB_H

#include <ruby.h>
#include <libssh/libssh.h>

extern VALUE rb_mlibssh;
extern VALUE rb_clibssh_connection;

void Init_libsshrb();
void Init_libsshrb_connection_class();

typedef struct ssh_connection
{
  ssh_session libssh_session;
} SSH_CONNECTION;

VALUE alloc_libssh_session(VALUE);
void free_libssh_session(SSH_CONNECTION*);

#endif
