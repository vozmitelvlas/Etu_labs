from fury import window, actor, utils, ui
import numpy as np
import itertools

radius_particle = 0.08
initial_velocity = 0.09
acc = 0.004
time = 0
incre_time = 0.09
angular_frq = 0.1
phase_angle = 0.002

scene = window.Scene()
scene.zoom(1.2)
scene.set_camera(position=(10, 12.5, 19), focal_point=(3.0, 0.0, 0.0),
                 view_up=(0.0, 0.0, 0.0))
showm = window.ShowManager(scene,
                           size=(800, 600), reset_camera=True,
                           order_transparent=True)
showm.initialize()

color_arrow = window.colors.blue  # цвет стрелы
centers = np.array([[0, 0, 0]])
directions = np.array([[1, 0, 0]])
heights = np.array([8])
arrow_actor = actor.arrow(centers, directions, color_arrow, heights,
                          resolution=20, tip_length=0.06, tip_radius=0.012,
                          shaft_radius=0.005)
scene.add(arrow_actor)

x = initial_velocity * time + 0.5 * acc * (time ** 2)
y = np.sin(angular_frq * time + phase_angle)
z = np.cos(angular_frq * time + phase_angle)

color_particle = window.colors.red  # цвет частицы
pts = np.array([[x, y, z]])
charge_actor = actor.point(pts, color_particle, point_radius=radius_particle)
scene.add(charge_actor)

vertices = utils.vertices_from_actor(charge_actor)
vcolors = utils.colors_from_actor(charge_actor, 'colors')
no_vertices_per_point = len(vertices)
initial_vertices = vertices.copy() - \
                   np.repeat(pts, no_vertices_per_point, axis=0)

tb = ui.TextBlock2D(bold=True, position=(100, 90))
m1 = "Motion of a charged particle in a "
m2 = "combined electric and magnetic field"
tb.message = m1 + m2
scene.add(tb)

counter = itertools.count()
end = 200

coor_1 = np.array([0, 0, 0])


def timer_callback(_obj, _event):
    global pts, time, incre_time, coor_1
    time += incre_time
    cnt = next(counter)

    x = initial_velocity * time + 0.5 * acc * (time ** 2)
    y = np.sin(10 * angular_frq * time + phase_angle)
    z = np.cos(10 * angular_frq * time + phase_angle)
    pts = np.array([[x, y, z]])

    vertices[:] = initial_vertices + \
                  np.repeat(pts, no_vertices_per_point, axis=0)

    utils.update_actor(charge_actor)

    # Plotting the path followed by the particle
    coor_2 = np.array([x, y, z])
    coors = np.array([coor_1, coor_2])
    coors = [coors]
    line_actor = actor.line(coors, window.colors.cyan, linewidth=3)
    scene.add(line_actor)
    coor_1 = coor_2

    showm.render()

    # to end the animation
    if cnt == end:
        showm.exit()


showm.add_timer_callback(True, 30, timer_callback)
showm.start()
#window.record(showm.scene, size=(800, 600), out_path="viz_helical_motion.png")
