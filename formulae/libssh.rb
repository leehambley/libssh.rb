require 'formula'

class Libssh <Formula

  url 'http://www.libssh.org/files/rc/libssh-0.4.91.tar.gz'
  homepage 'http://www.libssh.org/'
  md5 'cc5b22c26d8326224ba20920c53f8fe5'

  depends_on "glib"
  depends_on 'cmake'
  depends_on 'openssl'

  def install
    system "mkdir -p build"
    system "cd build && cmake -DCMAKE_INSTALL_PREFIX=#{prefix} .."
    system "cd build && make install"
  end
end
