#ifndef CTX_H
#define CTX_H

#ifndef MINI_INCLUDE
#error this file must only be included by minifilter.h
#endif

#define CTX_STRING_TAG                        'tSxC'
#define CTX_RESOURCE_TAG                      'cRxC'
#define CTX_INSTANCE_CONTEXT_TAG              'cIxC'
#define CTX_FILE_CONTEXT_TAG                  'cFxC'
#define CTX_STREAM_CONTEXT_TAG                'cSxC'
#define CTX_STREAMHANDLE_CONTEXT_TAG          'cHxC'

//
//  Instance context data structure
//

typedef struct _CTX_INSTANCE_CONTEXT {

} CTX_INSTANCE_CONTEXT, * PCTX_INSTANCE_CONTEXT;
#define CTX_INSTANCE_CONTEXT_SIZE         sizeof( CTX_INSTANCE_CONTEXT )

//
//  File context data structure
//

typedef struct _CTX_FILE_CONTEXT {
	
} CTX_FILE_CONTEXT, * PCTX_FILE_CONTEXT;

#define CTX_FILE_CONTEXT_SIZE         sizeof( CTX_FILE_CONTEXT )

//
//  Stream context data structure
//

typedef struct _CTX_STREAM_CONTEXT {

} CTX_STREAM_CONTEXT, * PCTX_STREAM_CONTEXT;

#define CTX_STREAM_CONTEXT_SIZE         sizeof( CTX_STREAM_CONTEXT )

//
//  Stream handle context data structure
//

typedef struct _CTX_STREAMHANDLE_CONTEXT {

} CTX_STREAMHANDLE_CONTEXT, * PCTX_STREAMHANDLE_CONTEXT;

#define CTX_STREAMHANDLE_CONTEXT_SIZE         sizeof( CTX_STREAMHANDLE_CONTEXT )
#endif