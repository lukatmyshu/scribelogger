Summary: scribelogger (logging interface to scribe)
Name: scribelogger
Version: 1.0.0
Release: %{?dist}.0
License: None
Group: System Environment/Libraries
URL: http://github.com/lukatmyshu/scribelogger
Source0: %{name}-%{version}.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root


%description
Logger to allow non-blocking daemons access to scribe

%prep
%setup -q

%build
FLAGS="%{optflags}" \
./configure \
  --prefix=%{_prefix} \
  --libdir=%{_libdir}
make

%install
rm -rf $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT install

%clean
rm -rf $RPM_BUILD_ROOT

%post

%preun

%files
%defattr(-,root,root,-)
%{_includedir}/
%{_libdir}/
%doc


%changelog

