Name:		pray5times
Version:	%{git_version}
Release:	%{patchlevel}.rc1%{?dist}
Summary:	Calculate prayers times
License:	MIT
Source:		%{name}-%{git_version}-%{?patchlevel}.tar.gz

%description
Calculate prayer times

%prep
%setup -qn pray5times

%build
make

%check
cd src/ && make check

%install
mkdir -p %{buildroot}/%{_bindir}
mkdir -p %{buildroot}/%{_mandir}

install -m 0755 src/%{name} %{buildroot}/%{_bindir}/%{name}
install -m 0755 wrapper/dist/%{name}-wrapper %{buildroot}/%{_bindir}/%{name}-wrapper
install -m 0755 src/%{name}.1 %{buildroot}/%{_mandir}/%{name}.1

%files
%{_bindir}/%{name}
%{_bindir}/%{name}-wrapper
%{_mandir}/%{name}.1

%changelog
* Mon Mar 07 2022 Mehdi Bendahhou <mehdi.bendahhou@gmail.com> - 0.0.0
- Initial version
