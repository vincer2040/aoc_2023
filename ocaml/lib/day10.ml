module Point = struct
  type t = int * int

  let compare (y1, x1) (y2, x2) =
    if y1 != y2 then y1 - y2 else if x1 != x2 then x1 - x2 else 0
  ;;
end

module PointSet = Set.Make (Point)

let filter_none line =
  match line with
  | "" -> false
  | _ -> true
;;

let is_connected_north pipes (y, x) =
  let n = y - 1 in
  if n < 0
  then false
  else (
    let row = List.nth pipes y in
    let pipe = String.get row x in
    match pipe with
    | '-' -> false
    | '7' -> false
    | 'F' -> false
    | _ ->
      let nrow = List.nth pipes n in
      let npipe = String.get nrow x in
      (match npipe with
       | '|' -> true
       | '7' -> true
       | 'F' -> true
       | _ -> false))
;;

let is_connected_south pipes (y, x) =
  let s = y + 1 in
  let num_rows = List.length pipes in
  if s >= num_rows
  then false
  else (
    let row = List.nth pipes y in
    let pipe = String.get row x in
    match pipe with
    | '-' -> false
    | 'L' -> false
    | 'J' -> false
    | _ ->
      let srow = List.nth pipes s in
      let spipe = String.get srow x in
      (match spipe with
       | '|' -> true
       | 'L' -> true
       | 'J' -> true
       | _ -> false))
;;

let is_connected_east pipes (y, x) =
  let e = x + 1 in
  let row_len = String.length (List.nth pipes 0) in
  if e >= row_len
  then false
  else (
    let row = List.nth pipes y in
    let pipe = String.get row x in
    match pipe with
    | '|' -> false
    | 'J' -> false
    | '7' -> false
    | _ ->
      let erow = List.nth pipes y in
      let epipe = String.get erow e in
      (match epipe with
       | '-' -> true
       | '7' -> true
       | 'J' -> true
       | _ -> false))
;;

let rec find_path pipes ~start:(y, x) ~cur:(y1, x1) path seen =
  if y == y1 && x == x1
  then path
  else if is_connected_north pipes (y1, x1)
          && PointSet.mem (y1 - 1, x1) seen != true
  then
    find_path
      pipes
      ~start:(y, x)
      ~cur:(y1 - 1, x1)
      ((y1, x1) :: path)
      (PointSet.add (y1, x1) seen)
  else if is_connected_south pipes (y1, x1)
          && PointSet.mem (y1 + 1, x1) seen != true
  then
    find_path
      pipes
      ~start:(y, x)
      ~cur:(y1 + 1, x1)
      ((y1, x1) :: path)
      (PointSet.add (y1, x1) seen)
  else if is_connected_east pipes (y1, x1)
          && PointSet.mem (y1, x1 + 1) seen != true
  then
    find_path
      pipes
      ~start:(y, x)
      ~cur:(y1, x1 + 1)
      ((y1, x1) :: path)
      (PointSet.add (y1, x1) seen)
  else
    find_path
      pipes
      ~start:(y, x)
      ~cur:(y1, x1 - 1)
      ((y1, x1) :: path)
      (PointSet.add (y1, x1) seen)
;;

let find_loop pipes (y, x) =
  if is_connected_north pipes (y, x)
  then find_path pipes ~start:(y, x) ~cur:(y - 1, x) [] PointSet.empty
  else if is_connected_south pipes (y, x)
  then find_path pipes ~start:(y, x) ~cur:(y + 1, x) [] PointSet.empty
  else if is_connected_east pipes (y, x)
  then find_path pipes ~start:(y, x) ~cur:(y, x + 1) [] PointSet.empty
  else find_path pipes ~start:(y, x) ~cur:(y, x - 1) [] PointSet.empty
;;

let rec find_start pipes num_rows row_len (y, x) =
  if x >= row_len
  then find_start pipes num_rows row_len (y + 1, 0)
  else if y >= num_rows
  then -1, -1
  else (
    let row = List.nth pipes y in
    let spot = String.get row x in
    if spot == 'S' then y, x else find_start pipes num_rows row_len (y, x + 1))
;;

let shoelace vertices =
  let n = List.length vertices in
  let rec loop i acc =
    if i = n - 1
    then
      acc
      + ((fst (List.nth vertices i) * snd (List.hd vertices))
         - (fst (List.hd vertices) * snd (List.nth vertices i)))
    else
      loop
        (i + 1)
        (acc
         + ((fst (List.nth vertices i) * snd (List.nth vertices (i + 1)))
            - (fst (List.nth vertices (i + 1)) * snd (List.nth vertices i))))
  in
  let result = loop 0 0 in
  abs result / 2
;;

let p1 input =
  let pipes = String.split_on_char '\n' input |> List.filter filter_none in
  let num_rows = List.length pipes in
  let row_len = String.length (List.nth pipes 0) in
  let start_y, start_x = find_start pipes num_rows row_len (0, 0) in
  let path = find_loop pipes (start_y, start_x) in
  let len = float_of_int (List.length path) in
  let res = len /. 2.0 |> ceil |> int_of_float in
  res
;;

let p2 input =
  let pipes = String.split_on_char '\n' input |> List.filter filter_none in
  let num_rows = List.length pipes in
  let row_len = String.length (List.nth pipes 0) in
  let start_y, start_x = find_start pipes num_rows row_len (0, 0) in
  let path =
    (start_y, start_x) :: find_loop pipes (start_y, start_x)
    |> List.map (fun (y, x) -> x, y)
  in
  let len = List.length path in
  let s = shoelace path in
  let x = (len / 2) - 1 in
  let r = s - x in
  r
;;
