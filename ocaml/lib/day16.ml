type dir =
  | Right
  | Left
  | Up
  | Down
[@@deriving show, eq]

module Point = struct
  type t = int * int

  let compare (ay, ax) (by, bx) =
    if ay != by then ay - by else if ax != bx then ax - bx else 0
  ;;
end

module PointDir = struct
  type t = dir * int * int

  let compare (dira, ay, ax) (dirb, by, bx) =
    if dira != dirb then 1 else Point.compare (ay, ax) (by, bx)
  ;;
end

module PointSet = Set.Make (Point)
module PointDirSet = Set.Make (PointDir)

let get_next_points layout (cur_y, cur_x) dir =
  let ch = String.get (List.nth layout cur_y) cur_x in
  match dir with
  | Right ->
    if ch == '\\'
    then [ Down, cur_y + 1, cur_x ]
    else if ch == '/'
    then [ Up, cur_y - 1, cur_x ]
    else if ch == '|'
    then [ Up, cur_y - 1, cur_x; Down, cur_y + 1, cur_x ]
    else [ Right, cur_y, cur_x + 1 ]
  | Left ->
    if ch == '\\'
    then [ Up, cur_y - 1, cur_x ]
    else if ch == '/'
    then [ Down, cur_y + 1, cur_x ]
    else if ch == '|'
    then [ Up, cur_y - 1, cur_x; Down, cur_y + 1, cur_x ]
    else [ Left, cur_y, cur_x - 1 ]
  | Up ->
    if ch == '\\'
    then [ Left, cur_y, cur_x - 1 ]
    else if ch == '/'
    then [ Right, cur_y, cur_x + 1 ]
    else if ch == '-'
    then [ Left, cur_y, cur_x - 1; Right, cur_y, cur_x + 1 ]
    else [ Up, cur_y - 1, cur_x ]
  | Down ->
    if ch == '\\'
    then [ Right, cur_y, cur_x + 1 ]
    else if ch == '/'
    then [ Left, cur_y, cur_x - 1 ]
    else if ch == '-'
    then [ Left, cur_y, cur_x - 1; Right, cur_y, cur_x + 1 ]
    else [ Down, cur_y + 1, cur_x ]
;;

let rec walk layout (cur_y, cur_x) dir energized seen =
  let row_len = String.length (List.nth layout 0) in
  let layout_len = List.length layout in
  if cur_y < 0 || cur_y >= layout_len
  then energized, seen
  else if cur_x < 0 || cur_x >= row_len
  then energized, seen
  else if PointDirSet.mem (dir, cur_y, cur_x) seen
  then energized, seen
  else (
    let energized = PointSet.add (cur_y, cur_x) energized in
    let seen = PointDirSet.add (dir, cur_y, cur_x) seen in
    let next_points = get_next_points layout (cur_y, cur_x) dir in
    let energized, seen =
      List.fold_left
        (fun (acce, accs) (d, y, x) -> walk layout (y, x) d acce accs)
        (energized, seen)
        next_points
    in
    energized, seen)
;;

let create_starts layout =
  let row_len = String.length (List.nth layout 0) in
  let layout_len = List.length layout in
  let top_starts = List.init row_len (fun i -> 0, i, Down) in
  let bottom_starts = List.init row_len (fun i -> layout_len - 1, i, Up) in
  let left_starts = List.init layout_len (fun i -> i, 0, Right) in
  let right_starts = List.init layout_len (fun i -> i, row_len - 1, Left) in
  let starts = top_starts @ bottom_starts @ left_starts @ right_starts in
  starts
;;

let p1 input =
  let input = String.trim input in
  let layout = String.split_on_char '\n' input in
  let energized, _ =
    walk layout (0, 0) Right PointSet.empty PointDirSet.empty
  in
  PointSet.cardinal energized
;;

let p2 input =
  let input = String.trim input in
  let layout = String.split_on_char '\n' input in
  let starts = create_starts layout in
  let res =
    List.fold_left
      (fun acc (y, x, dir) ->
        let energized, _ =
          walk layout (y, x) dir PointSet.empty PointDirSet.empty
        in
        let num = PointSet.cardinal energized in
        max acc num)
      0
      starts
  in
  res
;;
