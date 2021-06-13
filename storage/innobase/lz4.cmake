# Copyright (C) 2014, SkySQL Ab. All Rights Reserved.
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation; version 2 of the License.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with
# this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin St, Fifth Floor, Boston, MA 02110-1335 USA

SET(WITH_INNODB_LZ4 AUTO CACHE STRING
  "Build with lz4. Possible values are 'ON', 'OFF', 'AUTO' and default is 'AUTO'")

MACRO (MYSQL_CHECK_LZ4)
  IF (WITH_INNODB_LZ4 STREQUAL "ON" OR WITH_INNODB_LZ4 STREQUAL "AUTO")
    ADD_DEFINITIONS(-DHAVE_LZ4=1 -DHAVE_LZ4_COMPRESS_DEFAULT=1)
  ENDIF()
ENDMACRO()
