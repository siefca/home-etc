# $Revision: 1.10 $, $Date: 2003/12/07 17:58:56 $
Summary:	HOME-ETC support for PLD Linux
Summary(pl):	Wsparcie mechanizmu HOME-ETC dla PLD Linux
Name:		home-etc
Version:	1.0.3
Release:	1
Epoch:		1
License:	LGPL
Group:		Base
Requires:	coreutils
Requires:	shadow
Source0:	ftp://ftp.pld-linux.org/people/siefca/distfiles/%{name}-%{version}.tar.gz
# Source0-md5:	a8fb13ce505ac0a56c02ba34d44b3ea6
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

%package static
Summary:	Static version of HOME-ETC library
Summary(pl):	Wersja statyczna biblioteki HOME-ETC
License:	LGPL
Group:		Development/Libraries
Requires:	%{name}-devel = %{epoch}:%{version}

%description static
HOME-ETC is an idea to keep configuration files in a subdirectory
specified by user, instead of its home directory. This package
contains static elements of the library.

%description static -l pl
HOME-ETC jest pomys³em, aby przechowywaæ pliki konfiguracyjne
w podkatalogu wskazanym przez u¿ytkownika, zamiast bezpo¶rednio
w jego katalogu domowym. Pakiet ten zawiera statyczne elementy
biblioteki.

%package devel
Summary:	Header files for HOME-ETC
Summary(pl):	Pliki nag³ówkowe dla mechanizmu HOME-ETC
License:	LGPL
Group:		Development/Libraries
Requires:	%{name} = %{epoch}:%{version}

%description devel
HOME-ETC is an idea to keep configuration files in a subdirectory
specified by user, instead of its home directory. This package
contains header files needed to build HOME-ETC-compliant applications.

%description devel -l pl
HOME-ETC jest pomys³em, aby przechowywaæ pliki konfiguracyjne
w podkatalogu wskazanym przez u¿ytkownika, zamiast bezpo¶rednio
w jego katalogu domowym. Pakiet ten zawiera pliki nag³ówkowe
potrzebne do budowania aplikacji zgodnych z HOME-ETC.

%package examples
Summary:	Example files for HOME-ETC
Summary(pl):	Pliki przyk³adów dla mechanizmu HOME-ETC
License:	LGPL
Group:		Development/Libraries
Requires:	%{name}-devel = %{epoch}:%{version}

%description examples
HOME-ETC is an idea to keep configuration files in a subdirectory
specified by user, instead of its home directory. This package
contains examples, which explains how to modify existing applications.

%description examples -l pl
HOME-ETC jest pomys³em, aby przechowywaæ pliki konfiguracyjne
w podkatalogu wskazanym przez u¿ytkownika, zamiast bezpo¶rednio
w jego katalogu domowym. Pakiet ten zawiera pliki przyk³adów,
które wyja¶niaj± w jaki sposób modyfikowaæ istniej±ce aplikacje.

%prep
%setup -q

%build
%{__make} \
	CC="%{__cc}" \
	CFLAGS="%{rpmcflags} \$(WARN)"


%install
rm -rf $RPM_BUILD_ROOT
%{__make} install DESTDIR=$RPM_BUILD_ROOT
install -d $RPM_BUILD_ROOT%{_libdir}
install -d $RPM_BUILD_ROOT%{_bindir}
install -d $RPM_BUILD_ROOT%{_examplesdir}/%{name}-%{version}
install -d $RPM_BUILD_ROOT/etc/profile.d
install -d $RPM_BUILD_ROOT/etc/skel

%clean
rm -rf $RPM_BUILD_ROOT

%post   -p /sbin/ldconfig
%postun -p /sbin/ldconfig

%files
%defattr(644,root,root,755)
%doc FILES README CONTRIBUTORS AUTHORS COPYING TODO HOME-ETC.txt
%attr(755,root,root) %{_libdir}/lib*.so*
%attr(755,root,root) %{_libdir}/lib*.la
%attr(755,root,root) %{_bindir}/*
%attr(755,root,root) /etc/profile.d/home-etc.*sh
/etc/skel/.home_etc

%files devel
%defattr(644,root,root,755)
%{_includedir}/*.h

%files static
%defattr(644,root,root,755)
%attr(755,root,root) %{_libdir}/lib*.a

%files examples
%defattr(644,root,root,755)
%{_examplesdir}/%{name}-%{version}/*

%define date	%(echo `LC_ALL="C" date +"%a %b %d %Y"`)
%changelog
* %{date} PLD Team <feedback@pld-linux.org>
All persons listed below can be reached at <cvs_login>@pld-linux.org

$Log: home-etc.spec,v $
Revision 1.10  2003/12/07 17:58:56  siefca
- major fixes in interface
- Makefile for src fixed

Revision 1.9  2003/12/07 17:15:03  siefca
- version: 1.0.2

Revision 1.8  2003/12/07 17:06:11  siefca
- added auto-update to the home-etc migration script against list
- added patchwork dir containing working patches index
- added static safe wrapper for get_home_etc() and a macro for it
- naming convention modified; now _HE and _HEdir
- release 3

Revision 1.7  2003/12/05 17:21:50  siefca
- added ldconfig in post(un)
- fixed files section

Revision 1.6  2003/11/30 12:28:44  siefca
- typo fixed

Revision 1.5  2003/11/30 12:27:45  siefca
- static subpackage added

Revision 1.4  2003/11/28 18:05:25  siefca
- debugging removed from script
- Makefile fixes

Revision 1.3  2003/11/28 17:54:10  siefca
- examples subpackage added
- removed debugging switches from Makefile
- added home-etc migration script to the installing routines

Revision 1.2  2003/11/28 12:49:10  siefca
- Requires: coreutils
- RPM compliance in moving script

Revision 1.1  2003/11/26 19:33:25  siefca
- license changed to LGPL
- Makefiles for scripts and skeleton files
- more documentation
- Requires: shadow in specfile

Revision 1.4  2003/11/26 19:18:34  siefca
- epoch in the right place
- added todo about libtool and automake

Revision 1.3  2003/11/26 19:15:43  siefca
- documentation updated
- spec updated
- Makefiles fixed

Revision 1.2  2003/11/26 18:26:39  siefca
- updates

Revision 1.1.1.1  2003/11/26 18:10:58  siefca
- initial revision
