project('gfx', 
        'cpp',
        version : '1.0.0')

gfx_library = static_library('gfx',
                             'src/gfx/gfx.cpp',
                             include_directories : include_directories('include'),
                             link_args : ['-lGLFW'])

gfx_library_dep = declare_dependency(link_with : gfx_library, 
                                     include_directories : include_directories('include'),
                                     link_args : ['-lglfw'])

executable('gfx_test', 'gfx_test/main.cpp', dependencies : gfx_library_dep)
