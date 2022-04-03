#!/usr/bin/bash

TOP_DIR=$PWD
name=pray5times

clean() {
	rm -rf $TOP_DIR/release
	rm -rf $TOP_DIR/rpmbuild
	rm -rf $TOP_DIR/${name}_0.0-0
}

gen_tar() {
	git archive --format=tar.gz -o $TOP_DIR/$name-$version-$patchlevel.tar.gz \
		--prefix=pray5times/ main
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

gen_deb() {
	mkdir ${name}_0.0-0/
	mkdir -p ${name}_0.0-0/usr/bin
	mkdir -p ${name}_0.0-0/usr/lib64
	mkdir -p ${name}_0.0-0/usr/share/man/man1/
	mkdir ${name}_0.0-0/DEBIAN/

	make clean && make

	cp $TOP_DIR/src/$name $TOP_DIR/${name}_0.0-0/usr/bin
	cp $TOP_DIR/lib/libpray5times.so $TOP_DIR/${name}_0.0-0/usr/lib64
	cp $TOP_DIR/wrapper/dist/$name-wrapper $TOP_DIR/${name}_0.0-0/usr/bin
	cp $TOP_DIR/src/$name.1 $TOP_DIR/${name}_0.0-0/usr/share/man/man1/

	cp $TOP_DIR/control $TOP_DIR/${name}_0.0-0/DEBIAN

	dpkg-deb --build ${name}_0.0-0

	mkdir release/

	mv *.deb release/
}

arch=$(rpm --eval %{_arch})
version=$(git describe | cut -d "-" -f 1 | sed s/v//g)
patchlevel="$(git describe | cut -d "-" -f 2)"

if [ -z $patchlevel ]
then
	$patchlevel=""
fi

if [ $1 == "clean" ]
then
	clean
fi

if [ $1 == "rpm" ]
then
	gen_rpm
fi

if [ $1 == "deb" ]
then
	gen_deb
fi
