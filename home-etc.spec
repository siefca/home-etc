# $Revision: 1.1 $, $Date: 2003/11/26 19:33:25 $
Summary:	HOME-ETC support for PLD Linux
Summary(pl):	Wsparcie mechanizmu HOME-ETC dla PLD Linux
Name:		home-etc
Version:	1.0.1
Release:	1
Epoch:		1
License:	GPL
Group:		Base
Requires:	shadow
Source0:	ftp://ftp.pld-linux.org/people/siefca/distfiles/%{name}-%{version}.tar.gz
BuildRoot:	%{tmpdir}/%{name}-%{version}-root-%(id -u -n)

%description
HOME-ETC is an idea to keep configuration files in a subdirectory
specified by user, instead of its home directory. This package
provides support for it.

%description -l pl
HOME-ETC jest pomys�em, aby przechowywa� pliki konfiguracyjne
w podkatalogu wskazanym przez u�ytkownika, zamiast bezpo�rednio
w jego katalogu domowym. Pakiet ten zapewnia wsparcie dla tego
mechanizmu.

%package devel
Summary:	Header files for HOME-ETC
Summary(pl):	Pliki nag��wkowe dla mechanizmu HOME-ETC
License:	GPL
Group:		Development/Libraries
Requires:	%{name} = %{epoch}:%{version}

%description devel
HOME-ETC is an idea to keep configuration files in a subdirectory
specified by user, instead of its home directory. This package
contains header files needed to build HOME-ETC-compliant applications.

%description devel -l pl
HOME-ETC jest pomys�em, aby przechowywa� pliki konfiguracyjne
w podkatalogu wskazanym przez u�ytkownika, zamiast bezpo�rednio
w jego katalogu domowym. Pakiet ten zawiera pliki nag��wkowe
potrzebne do budowania aplikacji zgodnych z HOME-ETC.

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
install -d $RPM_BUILD_ROOT/etc/profile.d
install -d $RPM_BUILD_ROOT/etc/skel

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(644,root,root,755)
%doc FILES README CONTRIBUTORS AUTHORS COPYING TODO HOME-ETC.txt
%attr(755,root,root) %{_libdir}/lib*.so
%attr(755,root,root) /etc/profile.d/home-etc.*sh
/etc/skel/.home_etc

%files devel
%defattr(644,root,root,755)
%{_includedir}/*.h

%define date	%(echo `LC_ALL="C" date +"%a %b %d %Y"`)
%changelog
* %{date} PLD Team <feedback@pld-linux.org>
All persons listed below can be reached at <cvs_login>@pld-linux.org

$Log: home-etc.spec,v $
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