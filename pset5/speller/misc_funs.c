bool free_list_recursive(node *list_in)
{
	bool success = false;
	if ((list_in->next) != NULL)
	{
		success = free_list_recursive(list_in->next);
	}

	if (success)
	{
		free(list_in);
		return true;
	}
	else
	{
		return false;
	}
}

bool free_list(node *list_in)
{
	node *cursor = malloc(sizeof(node));
	if (cursor == NULL)
	{
		//printf("allocation failed");
		free(cursor);
		return false;
	}
	while (list_in->next != NULL)
	{
		////printf("%s", list_in->word);
		//cursor = list_in->next;
		//free(list_in);
		//list_in = cursor;
		list_in = list_in->next;
	}
	free(cursor);
	return true;
}

