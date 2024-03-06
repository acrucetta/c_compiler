

void init_vm_writer(const char *out_file);
void write_push(Segment segment, int index);
void write_pop(Segment segment, int index);
void write_arithmetic(Command command);
void write_label(const char *label);
void write_goto(const char *label);
void write_if(const char *label);
void write_call(const char *name, int n_args);
void write_function(const char *name, int n_locals);
void write_return();
void close_vm_writer();
