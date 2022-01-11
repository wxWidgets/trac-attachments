static struct hostent * deepCopyHostent(struct hostent *h,
					const struct hostent *he,
					char *buffer, int size, int *err)
{
  /* copy plain old structure */
  memcpy(h, he, sizeof(struct hostent));
  
  /* copy name */
  int len = strlen(h->h_name) + 1;
  if (size < len) {
    *err = ENOMEM;
    return NULL;
  }
  memcpy(buffer, h->h_name, len);
  h->h_name = buffer;

  /* track position in the buffer */
  int pos = len;

  /* reuse len to store address length */
  len = h->h_length;

  /* ensure pointer alignment */
  unsigned int misalign = sizeof(char *) - pos%sizeof(char *);
  if(misalign < sizeof(char *))
    pos += misalign;
  
  /* leave space for pointer list */
  char **p = h->h_addr_list, **q;
  char **h_addr_list = (char **)(buffer + pos);
  while(*(p++) != 0)
    pos += sizeof(char *);
  
  /* copy addresses and fill new pointer list */
  for (p = h->h_addr_list, q = h_addr_list; *p != 0; p++, q++) {
    if (size < len + pos){
      *err = ENOMEM;
      return NULL;
    }
    memcpy(buffer + pos, *p, len); /* copy content */
    *q = buffer + pos; /* set copied pointer to copied content */
    pos += len;
  }
  *++q = 0; /* null terminate the pointer list */
  h->h_addr_list = h_addr_list; /* copy pointer to pointers */
  
  /* ensure word alignment of pointers */
  misalign = sizeof(char *) - pos%sizeof(char *);
  if(misalign < sizeof(char *))
    pos += misalign;
  
  /* leave space for pointer list */
  p = h->h_aliases;
  char **h_aliases = (char **)(buffer + pos);
  while(*(p++) != 0)
    pos += sizeof(char *);
  
  /* copy aliases and fill new pointer list */
  for (p = h->h_aliases, q = h_aliases; size > 0 && *p != 0; p++, q++){
    len = strlen(*p) + 1;
    if (size < len + pos){
      *err = ENOMEM;
      return NULL;
    }
    memcpy(buffer + pos, *p, len);
    *q = buffer + pos;
    pos += len;
  }
  *++q = 0; /* null terminate the pointer list */
  h->h_aliases = h_aliases; /* copy pointer to pointers */

  return h;
}

 	  	 
