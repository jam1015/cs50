
bool in_string(int length_in, string name_in, string list_in[])
{
	for (int k = 0; k < length_in; k++)
	{
		if (strcmp(list_in[k], name_in) == 0)
		{
			return true;
		}
	}
	return false;
}

int string_position(string name_in, int length_in, string list_in[])
{
	for (int k = 0; k < length_in; k++)
	{
		if (strcmp(list_in[k], name_in) == 0)
		{
			return k;
		}
	}
	return -1;
}
