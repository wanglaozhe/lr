Action()
{
    int i = 20 - 1 ;
    char *param = (char *) malloc(4000);
	char transactionName[] = "promoCalculaCart20";
 
	strcpy(param,"Body={\"from\":\"cart\",\"productList\":[");
	for(;i>0;i--){
		strcat(param,lr_eval_string("{product_entry}"));
		strcat(param,",");
	}
	strcat(param,lr_eval_string("{product_entry}"));

	strcat(param,"],\"user\":{\"custId\":");
	strcat(param,lr_eval_string("{custId}"));
	strcat(param,",\"custType\":1,\"platform\":\"0\"}}");

	lr_output_message("param is %s",param);

	 //web_set_sockets_option("IGNORE_PREMATURE_SHUTDOWN", "1");
		 web_reg_save_param("RETURN_CODE",
		 "LB=\"code\":",
		 "RB=,",
		 "Ord=1",
		 "IgnoreRedirections=Yes",
		 LAST);

	 lr_start_transaction("promoCalcula");
	 lr_start_sub_transaction(transactionName,"promoCalcula");

	 web_custom_request(transactionName, 
			  "Method=POST", 
			  "URL=http://activity_qry_sv.idc4:8012/priceapi/calc/promo",param, 
			  "RecContentType=application/json",
			  "EncType=application/json",
			  LAST );

		 if(strcmp(lr_eval_string("{RETURN_CODE}"),"0")==0)
		 {
			 lr_end_sub_transaction(transactionName, LR_PASS);
		 }
		 else
		 {
			 lr_end_sub_transaction(transactionName, LR_FAIL);
		 }


		 if(strcmp(lr_eval_string("{RETURN_CODE}"),"0")==0)
		 {
																		 lr_end_transaction("promoCalcula", LR_PASS);
		}
		else
		{
			lr_end_transaction("promoCalcula", LR_FAIL);
		}

	free(param);
	
	return 0;
}
