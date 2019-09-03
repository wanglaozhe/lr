Action()
{
	web_reg_save_param("RETURN_CODE",
		"LB=\"errorCode\":\"",
		"RB=\"",
		"Ord=1",
		"IgnoreRedirections=Yes",
		LAST);
    web_set_sockets_option("IGNORE_PREMATURE_SHUTDOWN", "1");


	lr_start_transaction("promoRealTimeApi");

	lr_start_sub_transaction("promoRealTimeApi_1","promoRealTimeApi");

	web_custom_request("promoRealTimeApi_1", 
			 "Method=POST", 
			 "URL=http://10.5.25.133:8082/promoapi/find_product_promo",
			 "Body=[{\"productId\":{product1}}]",
			 "RecContentType=application/json",
			 "EncType=application/json",
			 LAST );

		if(strcmp(lr_eval_string("{RETURN_CODE}"),"0")==0)
		{
			lr_end_sub_transaction("promoRealTimeApi_1", LR_PASS);
		}
		else
		{
			lr_end_sub_transaction("promoRealTimeApi_1", LR_FAIL);
		}


		if(strcmp(lr_eval_string("{RETURN_CODE}"),"0")==0)
		{
			lr_end_transaction("promoRealTimeApi", LR_PASS);
		}
		else
		{
			lr_end_transaction("promoRealTimeApi", LR_FAIL);
		}
	return 0;
}
