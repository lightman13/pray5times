#!/usr/bin/bash

TOP_DIR=$PWD
name=prayer_time

clean() {
	rm -rf $TOP_DIR/release
	rm -rf $TOP_DIR/rpmbuild
}

gen_tar() {
	git archive --format=tar.gz -o $TOP_DIR/$name-$version.tar.gz \
		--prefix=muslim_prayer/ main
}

gen_rpm() {
	mkdir -p rpmbuild/{BUILD,BUILDROOT,RPMS,SOURCES,SPECS,SRPMS}

	gen_tar

	mv $name-$version.tar.gz $TOP_DIR/rpmbuild/SOURCES/

	rpmbuild --define "_topdir `pwd`/rpmbuild" --define "git_version $version" -bs $name.spec

	rpmbuild --define "_topdir `pwd`/rpmbuild" --define "git_version $version" --rebuild $TOP_DIR/rpmbuild/SRPMS/*.rpm

	mkdir release/

	cp $TOP_DIR/rpmbuild/RPMS/$arch/*.rpm $TOP_DIR/release/
	cp $TOP_DIR/rpmbuild/SRPMS/*.src.rpm $TOP_DIR/release/
}

arch=$(rpm --eval %{_arch})
version=$(git describe | sed s/v//g)

clean
gen_rpm
