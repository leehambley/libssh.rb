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

VALUE initialize_rb_clibssh_connection(VALUE self, VALUE hostname, VALUE options);
VALUE rb_clibssh_connection_hostname(VALUE self);

typedef struct rb_ssh_connection
{
  ssh_session libssh_session;
  char*       hostname;
} RB_SSH_CONNECTION;

VALUE alloc_rb_libssh_connection(VALUE);
void free_rb_libssh_connection(RB_SSH_CONNECTION*);


#endif
