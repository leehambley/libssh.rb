#ifndef LIBSSHRB_H
#define LIBSSHRB_H

#include <ruby.h>
#include <libssh/libssh.h>

extern VALUE rb_mlibssh;
extern VALUE rb_clibssh_connection;

extern VALUE rb_elibssh_error;
extern VALUE rb_elibssh_connection_error;

void Init_libsshrb();
void Init_rb_clibssh_connection();
void Init_rb_libssh_constants();

VALUE rb_clibssh_connection_initialize(int, VALUE*, VALUE);

typedef struct rb_ssh_connection
{
  ssh_session libssh_session;
} RB_SSH_CONNECTION;

VALUE alloc_libssh_session(VALUE);
void free_libssh_session(RB_SSH_CONNECTION*);


#endif
