module CharSet = Set.Make (Char)

let filter_none line =
  match line with
  | "" -> false
  | _ -> true
;;

let rec splice_list lst idx item =
  match lst, idx with
  | [], i when i > 0 -> failwith "Index out of bounds"
  | [], _ -> [ item ]
  | hd :: tl, i when i > 0 -> hd :: splice_list tl (i - 1) item
  | _, 0 -> item :: lst
  | _, _ -> failwith "Index out of bounds"
;;

let split_on_idx str idx =
  let str_len = String.length str in
  if idx < 0 || idx >= str_len
  then failwith "Index out of bounds"
  else (
    let prefix = String.sub str 0 idx in
    let suffix = String.sub str idx (str_len - idx) in
    prefix, suffix)
;;

let rec expand_rows solar_system idx =
  let create_new_galaxy () =
    let row_len = String.length (List.nth solar_system 0) in
    let new_str = String.make row_len '.' in
    let new_galaxy = splice_list solar_system idx new_str in
    new_galaxy
  in
  if idx >= List.length solar_system
  then solar_system
  else (
    let row = List.nth solar_system idx in
    let set =
      String.fold_left (fun acc char -> CharSet.add char acc) CharSet.empty row
    in
    if CharSet.cardinal set == 1
    then expand_rows (create_new_galaxy ()) (idx + 2)
    else expand_rows solar_system (idx + 1))
;;

let rec expand_columns solar_system idx =
  let row_len = String.length (List.nth solar_system 0) in
  let create_new_galaxy () =
    let add_to_galaxy row =
      let prefix, suffix = split_on_idx row idx in
      let new_row = prefix ^ "." ^ suffix in
      new_row
    in
    let new_galaxy = List.map add_to_galaxy solar_system in
    new_galaxy
  in
  if idx >= row_len
  then solar_system
  else (
    let add_to_set acc row =
      let ch = String.get row idx in
      CharSet.add ch acc
    in
    let set = List.fold_left add_to_set CharSet.empty solar_system in
    if CharSet.cardinal set == 1
    then expand_columns (create_new_galaxy ()) (idx + 2)
    else expand_columns solar_system (idx + 1))
;;

let rec get_row_expansions solar_system idx num_expansions expansions =
  if idx >= List.length solar_system
  then List.rev expansions
  else (
    let row = List.nth solar_system idx in
    let set =
      String.fold_left (fun acc ch -> CharSet.add ch acc) CharSet.empty row
    in
    if CharSet.cardinal set == 1
    then (
      let new_num_expansions = num_expansions + 1 in
      let new_expansions = new_num_expansions :: expansions in
      get_row_expansions
        solar_system
        (idx + 1)
        new_num_expansions
        new_expansions)
    else
      get_row_expansions
        solar_system
        (idx + 1)
        num_expansions
        (num_expansions :: expansions))
;;

let rec get_col_expansions solar_system idx num_expansions expansions =
  let row_len = String.length (List.nth solar_system 0) in
  if idx >= row_len
  then List.rev expansions
  else (
    let add_to_set acc row =
      let ch = String.get row idx in
      CharSet.add ch acc
    in
    let set = List.fold_left add_to_set CharSet.empty solar_system in
    if CharSet.cardinal set == 1
    then (
      let new_num_expansions = num_expansions + 1 in
      let new_expansions = new_num_expansions :: expansions in
      get_col_expansions
        solar_system
        (idx + 1)
        new_num_expansions
        new_expansions)
    else
      get_col_expansions
        solar_system
        (idx + 1)
        num_expansions
        (num_expansions :: expansions))
;;

let rec find_galaxies galaxies idx positions =
  if idx >= List.length galaxies
  then positions
  else (
    let row = List.nth galaxies idx in
    let add_galaxy (i, acc) ch =
      if ch == '#'
      then (
        let coord = idx, i in
        i + 1, coord :: acc)
      else i + 1, acc
    in
    let _, new_galaxies = String.fold_left add_galaxy (0, []) row in
    find_galaxies galaxies (idx + 1) (positions @ new_galaxies))
;;

let manhatten (y1, x1) (y2, x2) =
  let a = abs (x2 - x1) in
  let b = abs (y2 - y1) in
  a + b
;;

let num_times_to_expand = 1_000_000

let p1 input =
  let solar_system =
    String.split_on_char '\n' input |> List.filter filter_none
  in
  let expanded = expand_columns (expand_rows solar_system 0) 0 in
  let galaxy_coords = find_galaxies expanded 0 [] in
  let map = Hashtbl.create 10 in
  let create_list i =
    List.init (List.length galaxy_coords - i - 1) (fun x -> i + x + 1)
  in
  let add_point acc idx =
    let p = List.nth galaxy_coords idx in
    p :: acc
  in
  List.iteri
    (fun i (y, x) ->
      let l = create_list i in
      let to_points = List.fold_left add_point [] l |> List.rev in
      Hashtbl.add map (y, x) to_points)
    galaxy_coords;
  let get_dists (y, x) value acc =
    let get_dist acc (yi, xi) =
      let d = manhatten (y, x) (yi, xi) in
      acc + d
    in
    let dists = List.fold_left get_dist 0 value in
    acc + dists
  in
  let res = Hashtbl.fold get_dists map 0 in
  res
;;

let p2 input =
  let solar_system =
    String.split_on_char '\n' input |> List.filter filter_none
  in
  let row_expansions = get_row_expansions solar_system 0 0 [] in
  let col_expansions = get_col_expansions solar_system 0 0 [] in
  let galaxy_coords =
    find_galaxies solar_system 0 []
    |> List.map (fun (y, x) ->
      let row_exp = List.nth row_expansions y in
      let col_exp = List.nth col_expansions x in
      let new_y =
        if num_times_to_expand == 1
        then y + (row_exp * num_times_to_expand)
        else y + (row_exp * (num_times_to_expand - 1))
      in
      let new_x =
        if num_times_to_expand == 1
        then x + (col_exp * num_times_to_expand)
        else x + (col_exp * (num_times_to_expand - 1))
      in
      new_y, new_x)
  in
  let create_list i =
    List.init (List.length galaxy_coords - i - 1) (fun x -> i + x + 1)
  in
  let map = Hashtbl.create 10 in
  List.iteri
    (fun i (y, x) ->
      let l = create_list i in
      let add_point acc idx =
        let p = List.nth galaxy_coords idx in
        p :: acc
      in
      let to_points = List.fold_left add_point [] l |> List.rev in
      Hashtbl.add map (y, x) to_points)
    galaxy_coords;
  let get_dists (y, x) value acc =
    let get_dist acc (yi, xi) =
      let d = manhatten (y, x) (yi, xi) in
      acc + d
    in
    let dists = List.fold_left get_dist 0 value in
    acc + dists
  in
  let res = Hashtbl.fold get_dists map 0 in
  res
;;
