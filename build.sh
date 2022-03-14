#!/usr/bin/bash

TOP_DIR=$PWD
name=pray5times

clean() {
	rm -rf $TOP_DIR/release
	rm -rf $TOP_DIR/rpmbuild
}

gen_tar() {
	git archive --format=tar.gz -o $TOP_DIR/$name-$version-$patchlevel.tar.gz \
		--prefix=muslim_prayer/ main
}

gen_rpm() {
	mkdir -p rpmbuild/{BUILD,BUILDROOT,RPMS,SOURCES,SPECS,SRPMS}

	gen_tar

	mv $name-$version-$patchlevel.tar.gz $TOP_DIR/rpmbuild/SOURCES/

	rpmbuild --define "_topdir `pwd`/rpmbuild" --define "git_version $version"\
		--define "patchlevel $patchlevel" -bs $name.spec

	rpmbuild --define "_topdir `pwd`/rpmbuild" --define "git_version $version"\
		--define "patchlevel $patchlevel" --rebuild $TOP_DIR/rpmbuild/SRPMS/*.rpm

	mkdir release/

	cp $TOP_DIR/rpmbuild/RPMS/$arch/*.rpm $TOP_DIR/release/
	cp $TOP_DIR/rpmbuild/SRPMS/*.src.rpm $TOP_DIR/release/
}

arch=$(rpm --eval %{_arch})
version=$(git describe | cut -d "-" -f 1 | sed s/v//g)
patchlevel="$(git describe | cut -d "-" -f 2)"

if [ -z $patchlevel ]
then
	$patchlevel=""
fi

clean
gen_rpm
