#include <libsshrb.h>

VALUE rb_mLibSSH;
VALUE rb_cLibSSH_Connection;

VALUE rb_eLibSSH_Error;
VALUE rb_eLibSSH_ConnectionError;

void Init_libsshrb()
{
  rb_mLibSSH = rb_define_module("LibSSH");
  Init_libsshrb_constants();
  Init_rb_clibssh_connection();
}

void Init_libsshrb_constants()
{
  rb_eLibSSH_Error = rb_define_class_under(rb_mLibSSH, "Error", rb_eStandardError);
  rb_eLibSSH_ConnectionError = rb_define_class_under(rb_mLibSSH, "ConnectionError", rb_eLibSSH_Error);
}

void Init_rb_clibssh_connection()
{
  rb_cLibSSH_Connection = rb_define_class_under(rb_mLibSSH, "Connection", rb_cObject);
  rb_define_alloc_func(rb_cLibSSH_Connection, alloc_rb_libssh_connection);
  rb_define_method(rb_cLibSSH_Connection, "initialize", initialize_rb_clibssh_connection, 2);
  rb_define_method(rb_cLibSSH_Connection, "connected?", rb_clibssh_connection_connected_q, 0);
  rb_define_method(rb_cLibSSH_Connection, "hostname", rb_clibssh_connection_hostname, 0);
}

VALUE rb_clibssh_connection_connected_q(VALUE self)
{
  RB_SSH_CONNECTION *rb_ssh_connection;
  Data_Get_Struct(self, RB_SSH_CONNECTION, rb_ssh_connection);
  if(rb_ssh_connection->connected == 1){
    return Qtrue;
  }else{
    return Qfalse;
  }
}

VALUE rb_clibssh_connection_hostname(VALUE self)
{
  RB_SSH_CONNECTION *rb_ssh_connection;
  Data_Get_Struct(self, RB_SSH_CONNECTION, rb_ssh_connection);
  VALUE rb_shostname = ENCODED_STR_NEW2(rb_ssh_connection->hostname, "UTF-8");
  return rb_shostname;
}

VALUE initialize_rb_clibssh_connection(VALUE self, VALUE hostname, VALUE options)
{
  VALUE str;
  RB_SSH_CONNECTION *rb_ssh_connection;
  Data_Get_Struct(self, RB_SSH_CONNECTION, rb_ssh_connection);
  str = StringValuePtr(hostname);
  rb_ssh_connection->hostname = str;
  return rb_cLibSSH_Connection;
}

VALUE alloc_rb_libssh_connection(VALUE class)
{
  RB_SSH_CONNECTION *rb_ssh_connection = malloc(sizeof(RB_SSH_CONNECTION));
  rb_ssh_connection->libssh_session = ssh_new();
  if(rb_ssh_connection->libssh_session == NULL)
    rb_fatal("Unable to alloc at c function ssh_new()");
  VALUE obj = Data_Wrap_Struct(class, 0, free_rb_libssh_connection, rb_ssh_connection);
  return obj;
}

void free_rb_libssh_connection(RB_SSH_CONNECTION *rb_ssh_connection)
{
  ssh_free(rb_ssh_connection->libssh_session);
  free(rb_ssh_connection);
}

