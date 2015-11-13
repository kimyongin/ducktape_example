#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "duktape.h"

static int fileio_readfile(duk_context *ctx) {
	const char *filename = duk_to_string(ctx, 0);
	if (!filename) {
		goto error;
	}
	duk_push_string_file(ctx, filename);
	return 1;
error:
	return DUK_RET_ERROR;
}

void fileio_register(duk_context *ctx) {
	duk_push_global_object(ctx);
	duk_push_c_function(ctx, fileio_readfile, DUK_VARARGS);
	duk_put_prop_string(ctx, -2, "readFile");
	duk_pop(ctx);
}

int main(int argc, const char *argv[]) {
	duk_context *ctx = NULL;
	ctx = duk_create_heap_default();
	if (!ctx) {
		printf("Failed to create a Duktape heap.\n");
		exit(1);
	}
	fileio_register(ctx);
	if (duk_peval_file(ctx, "../module/fileB.js") != 0) {
		printf("Error: %s\n", duk_safe_to_string(ctx, -1));
		goto finished;
	}
	duk_pop(ctx);  /* ignore result */
finished:
	duk_destroy_heap(ctx);
	exit(0);
}