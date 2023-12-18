type point = int * int [@@deriving show]

module Point = struct
  type t = point

  let compare (ay, ax) (by, bx) =
    if ay != by then ay - by else if ax != bx then ax - bx else 0
  ;;
end

module PointSet = Set.Make (Point)
module PointMap = Map.Make (Point)

type dir =
  | Unspec
  | Up
  | Right
  | Down
  | Left
[@@deriving show, eq]

type edge = point * dir * int [@@deriving show]

let create_edges map (y, x) =
  let dirs = [ Up, -1, 0; Right, 0, 1; Down, 1, 0; Left, 0, -1 ] in
  let len = List.length map in
  let row_len = String.length (List.nth map 0) in
  List.fold_left
    (fun acc (dir, dy, dx) ->
      let ny = y + dy in
      let nx = x + dx in
      if ny < 0 || ny >= len || nx < 0 || nx >= row_len
      then acc
      else (
        let ch = String.get (List.nth map ny) nx in
        let weight = int_of_char ch - int_of_char '0' in
        let edge = (ny, nx), dir, weight in
        edge :: acc))
    []
    dirs
    |> List.rev
;;

let rec create_graph map graph seen (y, x) =
  if PointSet.mem (y, x) seen
  then graph, seen
  else (
    let seen = PointSet.add (y, x) seen in
    let edges = create_edges map (y, x) in
    let graph = PointMap.add (y, x) edges graph in
    List.fold_left
      (fun (g, s) ((ey, ex), _, _) -> create_graph map g s (ey, ex))
      (graph, seen)
      edges)
;;

let create_seen graph =
  PointMap.fold (fun k _ acc -> PointMap.add k false acc) graph PointMap.empty
;;

let create_prev graph =
  PointMap.fold
    (fun k _ acc -> PointMap.add k ((-1, -1), Unspec) acc)
    graph
    PointMap.empty
;;

let create_dist graph =
  PointMap.fold
    (fun k _ acc -> PointMap.add k Int.max_int acc)
    graph
    PointMap.empty
;;

let has_unvisited seen dists =
  PointMap.fold
    (fun k v acc ->
      if acc
      then acc
      else if v
      then acc
      else (
        let d = PointMap.find k dists in
        if d < Int.max_int then true else false))
    seen
    false
;;

let get_lowest_unvisited seen dists =
  let point, _ =
    PointMap.fold
      (fun k v (point, lowest) ->
        if v
        then point, lowest
        else (
          let dist = PointMap.find k dists in
          if lowest > dist then k, dist else point, lowest))
      seen
      ((-1, -1), Int.max_int)
  in
  point
;;

let rec get_last_three prev cur lst =
  if List.length lst == 3
  then lst
  else if Point.compare cur (-1, -1) == 0
  then lst
  else (
    let next, dir = PointMap.find cur prev in
    let lst = dir :: lst in
    get_last_three prev next lst)
;;

let cmp da db = if da != db then 1 else 0

let is_valid_dir prev cur next_dir =
  let last_three = get_last_three prev cur [] in
  if List.length last_three < 3
  then true
  else (
    let lst = List.init 3 (fun _ -> next_dir) in
    if List.compare cmp lst last_three == 0 then false else true)
;;

let dijkstra source sink graph =
  let seen_map = create_seen graph in
  let dist_map = create_dist graph |> PointMap.add source 0 in
  let prev_map = create_prev graph in
  let rec loop seen dists prev =
    if has_unvisited seen dists == false
    then prev
    else (
      let cur = get_lowest_unvisited seen dists in
      let seen = PointMap.add cur true seen in
      let adjs = PointMap.find cur graph in
      let dists, prev =
        List.fold_left
          (fun (ds, ps) (edge, dir, weight) ->
            if PointMap.find edge seen
            then ds, ps
            else (
              let dist = PointMap.find cur ds + weight in
              (*let edge_dist = PointMap.find edge ds in*)
              if (*dist < edge_dist &&*) is_valid_dir prev cur dir
              then (
                let ps = PointMap.add edge (cur, dir) ps in
                let ds = PointMap.add edge dist ds in
                ds, ps)
              else ds, ps))
          (dists, prev)
          adjs
      in
      loop seen dists prev)
  in
  let prev = loop seen_map dist_map prev_map in
  let rec create_path prev cur path =
    if Point.compare cur (-1, -1) = 0
    then path
    else (
      let path = cur :: path in
      let next, _ = PointMap.find cur prev in
      create_path prev next path)
  in
  create_path prev sink []
;;

let pop_first lst =
    match lst with
    | [] -> failwith "empty list"
    | _ :: tl -> tl
;;

let p1 input =
  let input = String.trim input in
  let map = String.split_on_char '\n' input in
  let graph, _ = create_graph map PointMap.empty PointSet.empty (0, 0) in
  Fmt.pr "%s\n" input;
  let endy = List.length map - 1 in
  let endx = String.length (List.nth map 0) - 1 in
  let path = dijkstra (0, 0) (endy, endx) graph |> pop_first in
  let res =
    List.fold_left
      (fun acc (y, x) ->
        let ch = String.get (List.nth map y) x in
        let num = int_of_char ch - int_of_char '0' in
        acc + num)
      0
      path
  in
  List.iter (fun p -> Fmt.pr "%s\n" (show_point p)) path;
  res
;;
