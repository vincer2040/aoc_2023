module CharSet = Set.Make (Char)

let filter_none line =
  match line with
  | "" -> false
  | _ -> true
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

let solve input num_times =
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
        if num_times == 1
        then y + (row_exp * num_times)
        else y + (row_exp * (num_times - 1))
      in
      let new_x =
        if num_times == 1
        then x + (col_exp * num_times)
        else x + (col_exp * (num_times - 1))
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

let p1 input = solve input 1
let p2 input = solve input 1_000_000
