package=randomx
$(package)_version=2.0.1
$(package)_download_path=https://codeload.github.com/tevador/RandomX/tar.gz/
$(package)_file_name=RandomX-$($(package)_version).tar.gz
$(package)_sha256_hash=cfa62704ab3c2fe85128a9987055edac44d02c7fd284673dec45f4f1fac7935
$(package)_build_subdir=build

define $(package)_set_vars
  $(package)_config_opts := -DARCH=generic -DBUILD_SHARED_LIBS=OFF -DARCH=native
  $(package)_config_opts += -DBUILD_TESTING=OFF
endef

define $(package)_config_cmds
  $($(package)_cmake) -S .. -B . $($(package)_config_opts)
endef

define $(package)_build_cmds
  $(MAKE)
endef

define $(package)_stage_cmds
  $(MAKE) DESTDIR=$($(package)_staging_dir) install
endef

define $(package)_postprocess_cmds
  rm -rf share
endef
