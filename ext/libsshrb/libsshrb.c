#include <libsshrb.h>

VALUE rb_mlibssh;
VALUE rb_clibssh_connection;

void Init_libsshrb()
{
  rb_mlibssh = rb_define_module("LibSSH");
  Init_libsshrb_connection_class();
}

/* void Init_libsshrb_exceptions()*/
/* {*/
/*   rb_define_class_under(rb_mlibssh, "Exception", );*/
/* }*/

void Init_libsshrb_connection_class()
{
  rb_clibssh_connection = rb_define_class_under(rb_mlibssh, "Connection", rb_cObject);
  rb_define_alloc_func(rb_clibssh_connection, alloc_libssh_session);
}

VALUE alloc_libssh_session(VALUE class)
{
  SSH_CONNECTION *ssh_connection_struct = malloc(sizeof(SSH_CONNECTION));
  ssh_connection_struct->libssh_session = ssh_new();
  if(ssh_connection_struct->libssh_session == NULL)
    rb_fatal("Unable to alloc at c function ssh_new()");
  VALUE obj = Data_Wrap_Struct(class, 0, free_libssh_session, ssh_connection_struct);
  return obj;
}

void free_libssh_session(SSH_CONNECTION *ssh_connection_struct)
{
  ssh_free(ssh_connection_struct->libssh_session);
  free(ssh_connection_struct);
}

