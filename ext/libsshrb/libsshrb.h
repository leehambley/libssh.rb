#ifndef LIBSSHRB_H
#define LIBSSHRB_H

#include <ruby.h>
#include <libssh/libssh.h>

#ifdef HAVE_RUBY_ENCODING_H

#include <ruby/encoding.h>

#define ENCODED_STR_NEW2(str, encoding) \
  ({ \
    VALUE _string = rb_str_new2((const char *)str); \
    int _enc = rb_enc_find_index(encoding); \
    rb_enc_associate_index(_string, _enc); \
    _string; \
  })

#else

#define ENCODED_STR_NEW2(str, encoding) \
  rb_str_new2((const char *)str)

#endif


extern VALUE rb_mLibSSH;
extern VALUE rb_cLibSSH_Connection;

extern VALUE rb_eLibSSH_Error;
extern VALUE rb_eLibSSH_ConnectionError;

void Init_libsshrb();
void Init_rb_clibssh_connection();
void Init_libsshrb_constants();

VALUE initialize_rb_clibssh_connection(VALUE self, VALUE hostname, VALUE options);
VALUE rb_clibssh_connection_hostname(VALUE self);
VALUE rb_clibssh_connection_connected_q(VALUE self);

typedef struct rb_ssh_connection
{
  ssh_session   libssh_session;
  unsigned char connected;
  char*         hostname;
} RB_SSH_CONNECTION;

VALUE alloc_rb_libssh_connection(VALUE);
void free_rb_libssh_connection(RB_SSH_CONNECTION*);


#endif
