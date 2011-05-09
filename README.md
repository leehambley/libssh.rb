# libssh.rb - Ruby Bindings for libssh

Ruby bindings for [libssh](http://www.libssh.org/), there is a similar project ([mallcop](https://github.com/tenderlove/mallcop)). Mallcop is build around `libssh2`, a very similar (but distinct from) library to `libssh`.

My emphasis will be on learning to build reliable, fast C extensions for Ruby,
and building something that integrates tightly with Capistrano, providing
minimum features, with outstanding documentation.

## Reasons

Ruby is not the ideal language for building crypto code with, owing to various 
issues. Mix-in, that yet-another implementation of well established algorithms 
is a waste of resources, bindings to popular, fully featured libraries with a
large community and extensive documentation allows us to make the most of the 
best tool for each job.

Ruby's extension architecture allows, and encourages C-extensions, and it is
my opinion that leveraging this to get great performance in critical
environments is key to the success of a library.

Further to that, I heard one too many complaints about `Net::SSH` performance
during my stewardship of `Capistrano`, and wanted to give something back.

A final reason is to eliminate the notion of access to a pseudo terminal, and
start a program of education for people who rely on SSH, to teach them about
the different kinds of connections, terminals, sessions and more, and to make
this knowledge accessible, useful, and usable.

## Goals

* Write a slim, but full-featured set of `libssh` bindings for Ruby.

* Support Ruby MRI 1.8.7, 1.9.2 and above.

* Try not to introduce code that precludes the support of alternative
  implementations

* Allow novice-users to understand the finer details of SSH, by borrowing
  from the exceptional documentation of the `libssh` project.

* Thorough, beautiful documentation with extensive examples using YARD.

## Installation

You will require `libssh`, available from [http://www.libssh.org/] or via your package manager:

    # port install libssh
    # brew install libssh
    # aptitude install libssh

*Note*: Currently, you'll need this homebrew installation: https://gist.github.com/963366 as the current release of libssh does not build cleanly on OSX.

See your platform (or package manager) specific notes on how and where this is installed. This Gem will search the usual unix prefix locations, for more information see [the mkmf configuration](). If the headers and library for `libssh` have been installed to somewhere else by your package manager, you may need to override the

## Defaults

    TODO

## Minimal Example

    TODO

## Extended Example

    TODO

## Timeline

* January 2011 - Start working, get a build against Ruby 1.9.2 & 1.8.7
* Febuary 2011 - Good test coverage of essential features.
* March 2011   - Introduce notion of pseudo terminals and streams.

## License

Note, until the project stabilizes, it is under the most draconian,
restrictive license I can find, basically because I don't want people to work
with, share and build on my broken code.

Until I find a suitable license, assume that this code is not free, it might 
be open source, but you have no permission to use it, for anything.

This will change as soon as there's a project with some momentum, but in the 
mean time this is to protect me from losing control of my work.

## Warranty

**None** it is important to understand that SSH is the back-bone of your
security, we all need it, we all have to trust it, and granting 3rd party code
access to your SSH keys, passwords, port configurations and more is very often
a massive security risk.

Whilst I work hard, to make a reliable, secure piece of software, I cannot be
held responsible for any damage caused, or losses incurred through malfunction
or misuse of this code, so in the spirit of most open source software, here is
the warranty:

    WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
    TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
    AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
    BE LIABLE FOR ANY CLAIM,

    DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
    OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
    THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## Testing

The tests are slightly unusual in that they boot an SSH server (using
your local implementation) in order to test the the Gem. For this to
work one needs to have `sshd` installed, and in the path, and able to
start on port `2234`. It also requires syslog, as DaemonController
requires a logfile to watch for errors, and the OpenSSH SSH
implementation cannot write directly to a log file, it instead must
write to `syslogd`. 

The tests expect that your syslogd is configured to write the
`local6`(`.*`) facility to `/var/log/libsshrb-test-sshd.log`.

To easily configure syslogd for this, simply add the following line to
the appropriate configuration file (on OSX this is `/etc/syslog.conf`

    local6.* /var/log/libsshrb-test-sshd.log

If you are on OSX you can restart syslog with:

    # launchctl unload /System/Library/LaunchDaemons/com.apple.syslogd.plist
    # launchctl load /System/Library/LaunchDaemons/com.apple.syslogd.plist

## Credits

Some parts of this code are inspired (sometimes heavily) by Carl Lerche's
`mallcop` gem, specifically in areas where my knowledge of building C
extensions for Ruby fell down.

Credit for the inspiration to keep working on things, even though I know they
are probably too difficult goes to [Pascal `paukul` Freiderich](http://www.github.com/paukul).

`libssh` is the reason this project has been possible, their contributor list is extensive, but can be found in []() in their source repository.
