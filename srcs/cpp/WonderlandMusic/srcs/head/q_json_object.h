#ifndef Q_JSON_OBJECT_H_H_HEAD__FILE__
#define Q_JSON_OBJECT_H_H_HEAD__FILE__
#define instaerJsonObj(insert_json_obj,var ) \
		insert_json_obj.insert( #var, QString("%1").arg( var ) )

#define getJsonObj(find_source_json_obj, var , find_result_iter, end_comp_iter, comp_result ) \
		(find_result_iter = find_source_json_obj.find( #var ),comp_result= (end_comp_iter == find_result_iter));

#define conver_string_find_var( find_source_json_obj, var , find_result_iter, end_comp_iter, comp_result , conver_string_function_name) \
	getJsonObj( find_source_json_obj, var, find_result_iter, end_comp_iter, comp_result ); \
	if( comp_result ) {  \
		string = find->toString( QString( "%1" ).arg( var ) ); \
		var = string.conver_string_function_name( &comp_result ); \
	}
#endif // Q_JSON_OBJECT_H_H_HEAD__FILE__
