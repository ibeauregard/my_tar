#include "archive.h"
#include "../utils/_string.h"
#include "fcntl.h"
#include "../constants.h"
#include "../error/error.h"
#include <unistd.h>
#include <stdlib.h>

#define ARCHIVE_FLAGS O_CREAT|O_WRONLY|O_TRUNC
#define ARCHIVE_MODE S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH

static int getArchiveFd(const char *archivePath);

int initArchive(Archive *archive, const char *archivePath)
{
	archive->fd = getArchiveFd(archivePath);
	if (archive->fd == SYSCALL_ERR_CODE) {
		return error(CANT_OPEN_FILE_ERR, archivePath);
	}
	archive->path = archivePath;
	return EXIT_SUCCESS;
}

int finalizeArchive(Archive *archive)
{
	return close(archive->fd);
}

int getArchiveFd(const char *archivePath)
{
	if (_strcmp(archivePath, STDOUT_PATH)) {
		return open(archivePath, ARCHIVE_FLAGS, ARCHIVE_MODE);
	}
	return STDOUT_FILENO;
}
