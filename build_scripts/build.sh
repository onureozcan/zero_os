#!/usr/bin/env bash
#download external files before build

function download_external_file() {
   DOWNLOAD_DIR=$1
   DOWNLOAD_URL=$2
   if [[ -f "$DOWNLOAD_DIR/master.zip" ]]; then
        echo "$DOWNLOAD_DIR/master.zip exist, skipping"
   else
       echo "downloading $DOWNLOAD_URL into $DOWNLOAD_DIR";

       mkdir -p $DOWNLOAD_DIR
       wget $DOWNLOAD_URL -O $DOWNLOAD_DIR/master.zip
       (cd $DOWNLOAD_DIR && \
       echo "unzipping into `pwd`" && \
       unzip master.zip);
   fi
}

./cmake_build.sh \
&& cd ../build_dir \
&& cp kernel ../iso/boot \
&& mkdir -p ../dist \
&& chmod 777 ../dist \
&& grub-mkrescue -o ../dist/os.iso ../iso \
&& chmod 777 ../dist/os.iso \
&& cd ../iso/boot \
&& objcopy --only-keep-debug kernel kernel.sym \
&& objcopy --strip-debug kernel

