# $Revision: 1.1 $, $Date: 2003/11/26 18:10:58 $
Summary:	HOME-ETC support for PLD Linux
Summary(pl):	Wsparcie mechanizmu HOME-ETC dla PLD Linux
Name:		home_etc
Version:	1.0.1
Release:	1
Epoch:		1
License:	GPL
Group:		Base
Source0:	ftp://ftp.pld-linux.org/software/utmp-jeber/%{name}-%{version}.tar.gz
BuildRoot:	%{tmpdir}/%{name}-%{version}-root-%(id -u -n)

%description
HOME-ETC is an idea to keep configuration files in a subdirectory
specified by user, instead of its home directory. This package
provides support for it.

%description -l pl
HOME-ETC jest pomys³em, aby przechowywaæ pliki konfiguracyjne
w podkatalogu wskazanym przez u¿ytkownika, zamiast bezpo¶rednio
w jego katalogu domowym. Pakiet ten zapewnia wsparcie dla tego
mechanizmu.

%package devel
Summary:	cron script for UTMP Jeber
Summary(pl):	Skrypt cyklicznego wykonywania dla UTMP Jeber
License:	GPL
Group:		Applications/System
Requires:	%{epoch}:%{name} = %{version}
Requires:	crontabs
Requires:	crondaemon
Requires:	syslogdaemon

%description devel
HOME-ETC is an idea to keep configuration files in a subdirectory
specified by user, instead of its home directory. This package
contains header files needed to build HOME-ETC-compliant applications.

%description devel -l pl
HOME-ETC jest pomys³em, aby przechowywaæ pliki konfiguracyjne
w podkatalogu wskazanym przez u¿ytkownika, zamiast bezpo¶rednio
w jego katalogu domowym. Pakiet ten zawiera pliki nag³ówkowe
potrzebne do budowania aplikacji zgodnych z HOME-ETC.

%prep
%setup -q -n %{name}-%{version}

%build
%{__make}

%install
rm -rf $RPM_BUILD_ROOT
%{__make} install DESTDIR=$RPM_BUILD_ROOT
install -d $RPM_BUILD_ROOT%{_bindir}

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(644,root,root,755)
%doc README README.polish ChangeLog NEWS AUTHORS KOPIOWANIE COPYING
%attr(755,root,root) %{_bindir}/*

%files cron
%defattr(644,root,root,755)
%attr(755,root,root) /etc/cron.hourly/%{name}

%define date	%(echo `LC_ALL="C" date +"%a %b %d %Y"`)
%changelog
* %{date} PLD Team <feedback@pld-linux.org>
All persons listed below can be reached at <cvs_login>@pld-linux.org

$Log: home_etc.spec,v $
Revision 1.1  2003/11/26 18:10:58  siefca
Initial revision


