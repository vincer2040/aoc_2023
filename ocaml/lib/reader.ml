let rec read path =
  match path with
  | Some p -> read_from_file p
  | None -> read_from_stdin ""

and read_from_file p =
  try
    let channel = open_in p in
    let contents = really_input_string channel (in_channel_length channel) in
    close_in channel;
    contents
  with
  | Sys_error _ -> ""

and read_from_stdin res =
  try
    let line = read_line () in
    read_from_stdin (res ^ line ^ "\n")
  with
  | End_of_file -> res
;;
