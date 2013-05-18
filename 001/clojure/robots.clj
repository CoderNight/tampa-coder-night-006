#!/usr/bin/env clj

(use 'clojure.java.io)

(if (nil? *command-line-args*)
  (do
    (println "Usage: clj robots.clj FILENAME")
    (System/exit 1)))

(def filename (first *command-line-args*))

(defn laser-test [char test]
  (if (and test (= char \|)) 1 0))

(defn rem-cycle [pos] 
  (drop pos (cycle '(true false))))

(defn process [[upper middle lower & r]]
  (let [pos (.indexOf middle "X")
        upper-west (map laser-test (take (inc pos) upper) (rem-cycle pos))
        upper-east (map laser-test (drop pos upper) (rem-cycle 0))
        lower-west (map laser-test (take (inc pos) lower) (rem-cycle (inc pos)))
        lower-east (map laser-test (drop pos lower) (rem-cycle 1))
        west (+ (reduce + upper-west) (reduce + lower-west))
        east (+ (reduce + upper-east) (reduce + lower-east))]
    (println (if (<= west east) "GO WEST" "GO EAST"))
    (if (not (nil? r )) (recur (rest r)))))


(with-open [rdr (reader filename)]
  (process (lazy-seq (line-seq rdr))))
