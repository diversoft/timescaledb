#ifndef TIMESCALEDB_HYPERTABLE_CACHE_H
#define TIMESCALEDB_HYPERTABLE_CACHE_H

#include <postgres.h>
#include "cache.h"

typedef struct PartitionEpoch PartitionEpoch;

#define HYPERTABLE_CACHE_INVAL_PROXY_TABLE "cache_inval_hypertable"
#define HYPERTABLE_CACHE_INVAL_PROXY_OID								\
	get_relname_relid(HYPERTABLE_CACHE_INVAL_PROXY_TABLE, CACHE_INVAL_PROXY_SCHEMA_OID)

#define MAX_EPOCHS_PER_HYPERTABLE 20

typedef struct Hypertable
{
	int32		id;
	char		time_column_name[NAMEDATALEN];
	Oid			time_column_type;
	int			num_epochs;
	int64		chunk_size_bytes;
	int16		num_replicas;
	/* Array of PartitionEpoch. Order by start_time */
	PartitionEpoch *epochs[MAX_EPOCHS_PER_HYPERTABLE];
}	Hypertable;


Hypertable *hypertable_cache_get_entry(Cache * cache, int32 hypertable_id);

PartitionEpoch *hypertable_cache_get_partition_epoch(Cache * cache, Hypertable * hce, int64 time_pt, Oid relid);

void		hypertable_cache_invalidate_callback(void);

extern Cache *hypertable_cache_pin(void);

void		_hypertable_cache_init(void);
void		_hypertable_cache_fini(void);

#endif   /* TIMESCALEDB_HYPERTABLE_CACHE_H */