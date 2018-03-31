/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.9 at Thu Mar 29 04:30:08 2018. */

#include "feature.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t tensorflow_BytesList_fields[2] = {
    PB_FIELD(  1, BYTES   , REPEATED, CALLBACK, FIRST, tensorflow_BytesList, value, value, 0),
    PB_LAST_FIELD
};

const pb_field_t tensorflow_FloatList_fields[2] = {
    PB_FIELD(  1, FLOAT   , REPEATED, CALLBACK, FIRST, tensorflow_FloatList, value, value, 0),
    PB_LAST_FIELD
};

const pb_field_t tensorflow_Int64List_fields[2] = {
    PB_FIELD(  1, INT64   , REPEATED, CALLBACK, FIRST, tensorflow_Int64List, value, value, 0),
    PB_LAST_FIELD
};

const pb_field_t tensorflow_Feature_fields[4] = {
    PB_FIELD(  1, MESSAGE , SINGULAR, STATIC  , FIRST, tensorflow_Feature, bytes_list, bytes_list, &tensorflow_BytesList_fields),
    PB_FIELD(  2, MESSAGE , SINGULAR, STATIC  , OTHER, tensorflow_Feature, float_list, bytes_list, &tensorflow_FloatList_fields),
    PB_FIELD(  3, MESSAGE , SINGULAR, STATIC  , OTHER, tensorflow_Feature, int64_list, float_list, &tensorflow_Int64List_fields),
    PB_LAST_FIELD
};

const pb_field_t tensorflow_Features_fields[2] = {
    PB_FIELD(  1, MESSAGE , REPEATED, CALLBACK, FIRST, tensorflow_Features, feature, feature, &tensorflow_Features_FeatureEntry_fields),
    PB_LAST_FIELD
};

const pb_field_t tensorflow_Features_FeatureEntry_fields[3] = {
    PB_FIELD(  1, STRING  , SINGULAR, CALLBACK, FIRST, tensorflow_Features_FeatureEntry, key, key, 0),
    PB_FIELD(  2, MESSAGE , SINGULAR, STATIC  , OTHER, tensorflow_Features_FeatureEntry, value, key, &tensorflow_Feature_fields),
    PB_LAST_FIELD
};

const pb_field_t tensorflow_FeatureList_fields[2] = {
    PB_FIELD(  1, MESSAGE , REPEATED, CALLBACK, FIRST, tensorflow_FeatureList, feature, feature, &tensorflow_Feature_fields),
    PB_LAST_FIELD
};

const pb_field_t tensorflow_FeatureLists_fields[2] = {
    PB_FIELD(  1, MESSAGE , REPEATED, CALLBACK, FIRST, tensorflow_FeatureLists, feature_list, feature_list, &tensorflow_FeatureLists_FeatureListEntry_fields),
    PB_LAST_FIELD
};

const pb_field_t tensorflow_FeatureLists_FeatureListEntry_fields[3] = {
    PB_FIELD(  1, STRING  , SINGULAR, CALLBACK, FIRST, tensorflow_FeatureLists_FeatureListEntry, key, key, 0),
    PB_FIELD(  2, MESSAGE , SINGULAR, STATIC  , OTHER, tensorflow_FeatureLists_FeatureListEntry, value, key, &tensorflow_FeatureList_fields),
    PB_LAST_FIELD
};


/* Check that field information fits in pb_field_t */
#if !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_32BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in 8 or 16 bit
 * field descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(tensorflow_Feature, bytes_list) < 65536 && pb_membersize(tensorflow_Feature, float_list) < 65536 && pb_membersize(tensorflow_Feature, int64_list) < 65536 && pb_membersize(tensorflow_Features_FeatureEntry, value) < 65536 && pb_membersize(tensorflow_FeatureLists_FeatureListEntry, value) < 65536), YOU_MUST_DEFINE_PB_FIELD_32BIT_FOR_MESSAGES_tensorflow_BytesList_tensorflow_FloatList_tensorflow_Int64List_tensorflow_Feature_tensorflow_Features_tensorflow_Features_FeatureEntry_tensorflow_FeatureList_tensorflow_FeatureLists_tensorflow_FeatureLists_FeatureListEntry)
#endif

#if !defined(PB_FIELD_16BIT) && !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_16BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in the default
 * 8 bit descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(tensorflow_Feature, bytes_list) < 256 && pb_membersize(tensorflow_Feature, float_list) < 256 && pb_membersize(tensorflow_Feature, int64_list) < 256 && pb_membersize(tensorflow_Features_FeatureEntry, value) < 256 && pb_membersize(tensorflow_FeatureLists_FeatureListEntry, value) < 256), YOU_MUST_DEFINE_PB_FIELD_16BIT_FOR_MESSAGES_tensorflow_BytesList_tensorflow_FloatList_tensorflow_Int64List_tensorflow_Feature_tensorflow_Features_tensorflow_Features_FeatureEntry_tensorflow_FeatureList_tensorflow_FeatureLists_tensorflow_FeatureLists_FeatureListEntry)
#endif


/* @@protoc_insertion_point(eof) */
