#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <iostream>
#include <vector>
#include "leveldb/db.h"

#define FUSE_USE_VERSION 26
#include <fuse.h>
/*
 * Key-Value File system(KVFS).
 * KVFS manages metadata in key-value store(currently using leveldb).
 * key is parent_ino(8bytes) : filename(32bytes)
 *
 */

using namespace std;

struct kvfs_data {
	leveldb::DB *kd_db;
};

#define KVFS_KEYLEN	(41)
#define KVFS_DATA ((struct kvfs_data *)fuse_get_context()->private_data)

/**
 * Imported from https://qiita.com/iseki-masaya/items/70b4ee6e0877d12dafa8
 */
vector<string> split_string(const string &s, char delim) {
	vector<string> elems;
	string item;
	for (char ch: s) {
		if (ch == delim) {
			if (!item.empty())
				elems.push_back(item);
			item.clear();
		}
		else {
			item += ch;
		}
	}
	if (!item.empty())
		elems.push_back(item);
	return elems;
}

static string kvfs_lookup_entry(unsigned long ino, const char *filename)
{
	char key_str[KVFS_KEYLEN + 1];
	string value;
	leveldb::Status status;

	/* copy \a ino and \a filename into \a key */
	snprintf(key_str, KVFS_KEYLEN, "%8lu:%s", ino, filename);

	/* get directory entry from db */
	status = KVFS_DATA->kd_db->Get(leveldb::ReadOptions(), key_str, &value);
	if (!status.ok()) {
		return "";
	} else {
		return value;
	}
}

static int kvfs_unpack_value(string value, struct stat *statbuf)
{
	return 0;
}

static int kvfs_lookup_getattr(const char *path, struct stat *statbuf)
{
	string path_str = path;
	vector<string> path_vec = split_string(path_str, '/');
	string value;

	/* lookup root */
	value = kvfs_lookup_entry(0, "root");

	/* walk component */
	for (vector<string>::iterator it = path_vec.begin();
		it != path_vec.end(); it++) {
		/* lookup key */
		;
		/* If key does not hit, return with -ENOENT */
	}

	kvfs_unpack_value(value, statbuf);
        //struct stat {
        //       dev_t     st_dev;         /* ID of device containing file */
        //       ino_t     st_ino;         /* inode number */
        //       mode_t    st_mode;        /* file type and mode */
        //       nlink_t   st_nlink;       /* number of hard links */
        //       uid_t     st_uid;         /* user ID of owner */
        //       gid_t     st_gid;         /* group ID of owner */
        //       dev_t     st_rdev;        /* device ID (if special file) */
        //       off_t     st_size;        /* total size, in bytes */
        //       blksize_t st_blksize;     /* blocksize for filesystem I/O */
        //       blkcnt_t  st_blocks;      /* number of 512B blocks allocated */
	//}
	statbuf->st_dev = 0;
	statbuf->st_ino = 0;
	statbuf->st_mode = S_IFDIR;
	statbuf->st_nlink = 1;
	statbuf->st_uid = 0;
	statbuf->st_gid = 0;
	statbuf->st_rdev = 0;
	statbuf->st_size = 4096;
	statbuf->st_blksize = 4096;
	statbuf->st_blocks = 4096;

	return 0;
}

int kv_getattr(const char *path, struct stat *statbuf)
{
	int rc;

	/*
	 * \a path is composed like "/foo/bar"
	 */

	rc = kvfs_lookup_getattr(path, statbuf);
}

int kv_readlink(const char *path, char *link, size_t size)
{
	return -EINVAL;
}

/* TODO: implement */
int kv_mknod(const char *path, mode_t mode, dev_t dev)
{
	return -EINVAL;
}

/* TODO: implement */
int kv_mkdir(const char *path, mode_t mode)
{
	return -EINVAL;
}

/* TODO: implement */
int kv_unlink(const char *path)
{
	return -EINVAL;
}

int kv_rmdir(const char *path)
{
	return -EINVAL;
}

int kv_symlink(const char *path, const char *link)
{
	return -EINVAL;
}

int kv_rename(const char *path, const char *newpath)
{
	return -EINVAL;
}

int kv_link(const char *path, const char *newpath)
{
	return -EINVAL;
}

int kv_chmod(const char *path, mode_t mode)
{
	return -EINVAL;
}

int kv_chown(const char *path, uid_t uid, gid_t gid)
{
	return -EINVAL;
}

int kv_truncate(const char *path, off_t newsize)
{
	return -EINVAL;
}

int kv_utime(const char *path, struct utimbuf *ubuf)
{
	return -EINVAL;
}

/* TODO: implement */
int kv_open(const char *path, struct fuse_file_info *fi)
{
	return -EINVAL;
}

int kv_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
	return -EINVAL;
}

int kv_write(const char *path, const char *buf, size_t size, off_t offset,
	     struct fuse_file_info *fi)
{
	return -EINVAL;
}

/* TODO: implement */
int kv_statfs(const char *path, struct statvfs *statv)
{
	return -EINVAL;
}

/* TODO: implement */
int kv_flush(const char *path, struct fuse_file_info *fi)
{
	return -EINVAL;
}
/* TODO: implement */
int kv_release(const char *path, struct fuse_file_info *fi)
{
	return -EINVAL;
}

int kv_fsync(const char *path, int datasync, struct fuse_file_info *fi)
{
	return -EINVAL;
}

int kv_setxattr(const char *path, const char *name, const char *value, size_t size, int flags)
{
	return -EINVAL;
}

int kv_getxattr(const char *path, const char *name, char *value, size_t size)
{
	return -EINVAL;
}

int kv_listxattr(const char *path, char *list, size_t size)
{
	return -EINVAL;
}

int kv_removexattr(const char *path, const char *name)
{
	return -EINVAL;
}

/* TODO: implement */
int kv_opendir(const char *path, struct fuse_file_info *fi)
{
	return -EINVAL;
}

/* TODO: implement */
int kv_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset,
	       struct fuse_file_info *fi)
{
	return -EINVAL;
}

/* TODO: implement */
int kv_releasedir(const char *path, struct fuse_file_info *fi)
{
	return -EINVAL;
}

/* TODO: implement */
int kv_fsyncdir(const char *path, int datasync, struct fuse_file_info *fi)
{
	return 0;
}

/* TODO: implement */
void *kv_init(struct fuse_conn_info *conn)
{
	return KVFS_DATA;
}

/* TODO: implement */
void kv_destroy(void *userdata)
{
	;
}

/* TODO: implement */
int kv_access(const char *path, int mask)
{
	return -EACCES;
}

int kv_ftruncate(const char *path, off_t offset, struct fuse_file_info *fi)
{
	return -EINVAL;
}

int kv_fgetattr(const char *path, struct stat *statbuf, struct fuse_file_info *fi)
{
	return -EINVAL;
}

static struct fuse_operations kv_oper;
//static struct fuse_operations kv_oper = {
//	.getattr     = kv_getattr,
//	.readlink    = kv_readlink,
//	.mknod       = kv_mknod,
//	.mkdir       = kv_mkdir,
//	.unlink      = kv_unlink,
//	.rmdir       = kv_rmdir,
//	.symlink     = kv_symlink,
//	.rename      = kv_rename,
//	.link        = kv_link,
//	.chmod       = kv_chmod,
//	.chown       = kv_chown,
//	.truncate    = kv_truncate,
//	.open        = kv_open,
//	.read        = kv_read,
//	.write       = kv_write,
//	.statfs      = kv_statfs,
//	.flush       = kv_flush,
//	.release     = kv_release,
//	.fsync       = kv_fsync,
//	.setxattr    = kv_setxattr,
//	.getxattr    = kv_getxattr,
//	.listxattr   = kv_listxattr,
//	.removexattr = kv_removexattr,
//	.opendir     = kv_opendir,
//	.readdir     = kv_readdir,
//	.releasedir  = kv_releasedir,
//	.fsyncdir    = kv_fsyncdir,
//	.init        = kv_init,
//	.destroy     = kv_destroy,
//	.access      = kv_access,
//	.create      = NULL,
//	.ftruncate   = kv_ftruncate,
//	.fgetattr    = kv_fgetattr,
//	.lock        = NULL,
//	.utimens     = NULL,
//	.bmap        = NULL,
//	.ioctl       = NULL,
//	.poll        = NULL,
//};
//
/* 280 has no meaning. I just set # larger enough than \a path */
#define DBPATH_LEN 280

int main(int argc, char **argv)
{
	struct kvfs_data *kd;
	leveldb::Options options;
	leveldb::Status status;
	char path[256], dbpath[DBPATH_LEN]; 
	int rc;

	/* Set operations */
	kv_oper.getattr = kv_getattr;

	/**/
	kd = (struct kvfs_data *)malloc(sizeof(*kd));

	if (realpath(argv[1], path) == NULL) {
		fprintf(stderr, "cannot canonicalize path %s.\n", argv[1]);
		goto free_kd;
	}
	snprintf(dbpath, DBPATH_LEN, "%s/.kvfs", path);
	options.create_if_missing = true;
	status = leveldb::DB::Open(options, dbpath, &kd->kd_db);
	if (!status.ok()) {
		fprintf(stderr, "open kvfs db failed.\n");
		goto free_kd;
	}

	argv[argc-2] = argv[argc-1];
	argv[argc-1] = NULL;
	argc--;
	rc = fuse_main(argc, argv, &kv_oper, kd);
	if (rc < 0) {
		fprintf(stderr, "fuse_main failed with rc = %d.\n", rc);
	}
out:
	return rc;
free_kd:
	free(kd);
err_out:
	return rc;
}
